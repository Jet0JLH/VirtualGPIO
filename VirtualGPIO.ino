/*
 * Copyright by Jet0JLH
 * 
 * 
 */
boolean pins[48][2];
const byte firstDigitalPin = 2;
const byte lastDigitalPin = 13;
const String Version = "Version 0.1";
byte tempByte;
byte src[4]; //*SerialReadedCommand

void setup() {
  Serial.begin(1000000);
  initPins();
  Serial.println(Version);
}

void loop() {
  while (Serial.available()) {
    tempByte = Serial.read();
      switch(tempByte) {
        case 4: //ASCII 4 stands for EOT=End Of Transmission
          executeCmd();
          break;
        case 24: //ASCII 24 stands for Cancel
          for (byte i=0;i<4;i++) { //Clear src Array
            src[i] = 0;
          }
          break;

        default:
          writeToSrc(tempByte); //Add Byte to src Array
          break;
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
void setValue(byte pin,boolean value) {
  digitalWrite(pin, value);
  pins[pin][1] = value;
}
void executeCmd() {
  switch(src[0]) {
    case 63: //ASCCI 63 stands for '?' = Help
      Serial.println("VirtualGPIO by Jet0JLH");
      Serial.println(Version);
      break;
    case 33: //setDirection
      setDirection(src[1]-65,src[2]);
      Serial.print(0);
      break;
    case 34: //setValue
      setValue(src[1]-65,src[2]);
      Serial.print(0);
      break;
    case 35: //getDirection
      Serial.print(pins[src[1]-65][0]);
      break;
    case 36: //getValue
      Serial.print(pins[src[1]-65][1]);
      break;
  }
}

