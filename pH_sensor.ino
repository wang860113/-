#include <SoftwareSerial.h>
SoftwareSerial Ser1(4, 11); //電導度
//SoftwareSerial Ser2(5, 13); //水分計
//SoftwareSerial Ser3(9, 3); //LoRa
//SoftwareSerial Ser4(15, 2);
//Set up (RX, TX) pins^

void setup() {
  Serial.begin(19200);
  Serial.setTimeout(500);
  Ser1.begin(19200);
  Ser1.setTimeout(500);
  //  Ser2.begin(9600);
  //  Ser2.setTimeout(500);
  //  Ser3.begin(19200);
  //  Ser3.setTimeout(500);
}
bool rxflag = false;
void loop()
{
  int i = 0;
  //Serial.println("test");
  //  while (1) {
  String s = "", us = "", ph = "", percent = "TEST";
  String c = "", data = "";
  String rxData;
  char rxByte;
  unsigned long startime;
  unsigned long stoptime;
  unsigned long total;
  //Ser3.listen();
  //  rxflag = false;
  //  if (Serial.available()) {
  //    delay(500);
  //    while (Serial.available()) {
  //
  //      rxByte = Serial.read();
  //      rxData += rxByte;
  //    }
  //    //Serial.print("Rx AT command: "); Serial.print(rxData);
  //    //Ser3.end();
  //    delay(500);

  if (rxflag) //if (rxData == "+RCV=45,5,00" )
  {
    startime = millis();
    rxflag = false;
    while (Ser1.available() > 0) {
      c = Ser1.readString();
      s += c;
    }


    int firstus = s.indexOf('⸮S/cm');
    us = s.substring(firstus - 10, firstus + 1);
    while (firstus == -1) {
      while (Ser1.available() > 0) {
        c = Ser1.readString();
        s += c;
      }
      firstus = s.indexOf('⸮S/cm');
      us = s.substring(firstus - 10, firstus + 1);
    }
    int firstph = s.indexOf('p');
    while (firstph == -1) {
      while (Ser1.available() > 0) {
        c = Ser1.readString();
        s += c;
      }
      firstph = s.indexOf('p');
    }
    ph = s.substring(firstph - 7, firstph + 2);
    data = us + ph ;//+ percent + "i" + i;
    stoptime = millis();
    total = stoptime - startime ;

    delay(4200 - total);
    Serial.println("AT+SEND=45,30," + data );
  }
}

void serialEvent() {
  String rxData;
  char rxByte;
  if (Serial.available()) {
    delay(500);
    while (Serial.available()) {
      rxByte = Serial.read();
      rxData += rxByte;
    }
  }
  if (rxData == "+RCV=45,5,00" ) {
    rxflag = true;
  }
  else {
    rxflag = false;
  }
}
