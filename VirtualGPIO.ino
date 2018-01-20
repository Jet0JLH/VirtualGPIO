/*
 * Copyright by Jet0JLH
 * 
 * 
 */

String inputString1 = "";
String inputString2 = "";
String inputString3 = "";
String inputString4 = "";
const String Version = "Version 0.1";
const byte firstDigitalPin = 2;
const byte firstAnalogPin = 0;
const byte lastDigitalPin = 13;
const byte lastAnalogPin = 7;
int activeString = 0;
boolean stringComplete = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(1000000);
  inputString1.reserve(200);
  inputString2.reserve(200);
  inputString3.reserve(200);
  inputString4.reserve(200);
  while (!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("VirtualGPIO " + Version);
  initPins();
  Serial.println("[READY]");
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available() == 0);
  activeString = 0;
  inputString1 = "";
  inputString2 = "";
  inputString3 = "";
  inputString4 = "";
  stringComplete = false;
  serialEvent();
  inputString1.toLowerCase();
  inputString2.toLowerCase();
  inputString3.toLowerCase();
  inputString4.toLowerCase();
  selectCmd();
}

void selectCmd() {
  if (inputString1 == "version") {
    Serial.println(Version);
  }
  else if (inputString1 == "get") {
    if (inputString2 == "direction") {
      Serial.println(getPin(inputString3));
    }
    else if (inputString2 == "value") {
      
    }
    else {
      printError(2);
    }
  }
  else if (inputString1 == "set") {
    if (inputString2 == "direction") {
      if (isAnalog(inputString3)) {
        if (inputString4 == "0" || inputString4 == "input") {
          pinMode(A0 + getPin(inputString3),INPUT);
        }
        else if (inputString4 == "1" || inputString4 == "output") {
          pinMode(A0 + getPin(inputString3),OUTPUT);
        }
        else {
          printError(4);
          return;
        }
      }
      else {
        if (inputString4 == "0" || inputString4 == "input") {
          pinMode(getPin(inputString3),INPUT);
        }
        else if (inputString4 == "1" || inputString4 == "output") {
          pinMode(getPin(inputString3),OUTPUT);
        }
        else {
          printError(4);
          return;
        }
      }
      Serial.println("Write direction [OK]");
    }
    else if (inputString2 == "value") {
      if (isAnalog(inputString3)) {
        if (inputString4 == "0" || inputString4 == "low") {
          digitalWrite(A0 + getPin(inputString3),LOW);
        }
        else if (inputString4 == "1" || inputString4 == "high") {
          digitalWrite(A0 + getPin(inputString3),HIGH);
        }
        else {
          printError(3);
          return;
        }
      }
      else {
        if (inputString4 == "0" || inputString4 == "low") {
          digitalWrite(getPin(inputString3),LOW);
        }
        else if (inputString4 == "1" || inputString4 == "high") {
          digitalWrite(getPin(inputString3),HIGH);
        }
        else {
          printError(3);
          return;
        }
        
      }
      Serial.println("Write value [OK]");
    }
  }
  else {
    printError(1);
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      return;
    }
    else if (inChar == ' ') {
      if (activeString >= 4) {
        inputString4 += inChar;
      }
      activeString ++;
    }
    else {
      // add it to the inputString:
      if (activeString == 0) {
        inputString1 += inChar;
      }
      else if (activeString == 1) {
        inputString2 += inChar;
      }
      else if (activeString == 2) {
        inputString3 += inChar;
      }
      else {
        inputString4 += inChar;
      }
      
    }
  }
}
void printError(int code) {
  switch (code) {
    case 1: {
      Serial.println("Error 1 Unknown command");
      break;
    }
    case 2: {
      Serial.println("Error 2 Unknown commandparameter");
      break;
    }
    case 3: {
      Serial.println("Error 3 Unknown value");
      break;
    }
    case 4: {
      Serial.println("Error 3 Unknown direction");
      break;
    }
  }
}
boolean isAnalog(String pin) {
  if (pin.startsWith("a")) {
    return true;
  }
  else {
    return false;
  }
}
int getPin(String pin) {
  if (pin.startsWith("a") || pin.startsWith("d")) {
    return pin.substring(1).toInt(); 
  }
  else {
    return pin.toInt();
  }
}

void initPins() {
  //Init DigitalPins as Outputs
  for (int i=firstDigitalPin; i < lastDigitalPin + 1; i++) {
    pinMode(i, OUTPUT);
  }
  //Init AnalogPins as Outputs
  for (int i=firstAnalogPin + A0; i < lastAnalogPin + 1 + A0; i++) {
    pinMode(i, OUTPUT);
  }
  
}

