#include <SoftwareSerial.h>
SoftwareSerial RYLR890 (8, 9); //(RX | TX)
const char Ack1[3] = {0x2A, 0x0D, 0x0A};
const char Ack2[14] = {0x41, 0x54, 0x2B, 0x41, 0x44, 0x44, 0x52, 0x45, 0x53, 0x53, 0x3D, 0x3F, 0x0D, 0x0A};
unsigned char inByte;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  RYLR890.begin(19200);
}

void loop() {
  String s = "";
  String rxData;
  char rxByte;
  if (RYLR890.available()) {
    delay(500);
    while (RYLR890.available()) {
      rxByte = RYLR890.read();
      rxData += rxByte;
    }
    Serial.print("Rx AT command: "); Serial.print(rxData);
    if (rxData == "+RCV=45,5,00" ) {
      delay(500);
      while (Serial.available()) {
        char inByte = (char)Serial.read();
        s += inByte;
      }
      Serial.println(Ack1[0]);
      Serial.println(s);
      RYLR890.println("AT+SEND=45,30," + s);
      delay(1000);
    }
  }
}
