/*
 * Copyright by Jet0JLH
 * 
 * 
 */
boolean pins[47][1];
const byte firstDigitalPin = 2;
const byte lastDigitalPin = 13;
const String Version = "Version 0.1";
byte tempByte;
byte src[3]; //*SerialReadedCommand

void setup() {
  Serial.begin(1000000);
  initPins();
  Serial.println(Version);
}

void loop() {
  while (Serial.available()) {
    tempByte = Serial.read();
    Serial.println(tempByte);
    
      
      if (tempByte == 24) { //ASCII 24 stands for Cancel
        for (byte i=0;i<4;i++) { //Clear src Array
          src[i] = 0;
        }
      }
      else if (tempByte == 4) {  //ASCII 4 stands for EOT=End Of Transmission
        Serial.print("Execute");
        Serial.print(src[0]);
        Serial.print(",");
        Serial.print(src[1]);
        Serial.print(",");
        Serial.print(src[2]);
        Serial.print(",");
        Serial.println(src[3]);
      }
      else { 
        writeToSrc(tempByte); //Add Byte to src Array
      }
      
    
  }
}
void initPins() {
  //Init DigitalPins as Outputs
  for (int i=firstDigitalPin; i < lastDigitalPin + 1; i++) {
    setDirection(i, OUTPUT);
  }
  setDirection(A0, OUTPUT);
  setDirection(A1, OUTPUT);
  setDirection(A2, OUTPUT);
  setDirection(A3, OUTPUT);
  setDirection(A4, OUTPUT);
  setDirection(A5, OUTPUT);
  setDirection(A6, OUTPUT);
  setDirection(A7, OUTPUT);
}
void writeToSrc(byte value) {
  for (byte i=0;i<3;i++) {
    src[i] = src[i + 1];
  }
  src[3] = value;
}
void setDirection(byte pin,boolean directionVal) {
  pinMode(pin, directionVal);
  pins[pin][0] = directionVal;
}

