#include <SoftwareSerial.h>
SoftwareSerial Ser2(5, 13); //水分計
void setup() {
  Serial.begin(19200);
  Serial.setTimeout(500);
  Ser2.begin(9600);
  Ser2.setTimeout(500);
}
bool rxflag = false;
void loop() {
  String s = "", us = "", ph = "", percent = "";
  String c = "", data = "";
  String rxData;
  char rxByte;
  unsigned long startime;
  unsigned long stoptime;
  unsigned long total;
    if(rxflag) {
      startime = millis();
      Ser2.listen(); // Select Ser2 for receiving
      delay(1000); // Give it time to send a response
      while ((Ser2.available() > 0)) {

        char h = Ser2.read();
        percent += h;
        s += h;
        //Serial.write(h);
      }
      Ser2.end();
      int per = percent.indexOf('4');
      percent = percent.substring(per + 9, per + 14);
      //      Serial.print("percent:"); Serial.println(percent);
      //      Serial.print("S:"); Serial.println(s);
      data = percent ;
      Serial.println("AT+SEND=45,10," + data );

      
    }
   rxflag = false;
  }
  //delay(1000);

void serialEvent() {
  String rxData;
  char rxByte;
 if(Serial.available()){
  delay(500);
  while (Serial.available()) {
    rxByte = Serial.read();
    rxData += rxByte;
  }
 }
//  Serial.println("rxdata:");
//  Serial.println(rxData);
  if (rxData == "+RCV=45,5,00" ){
    rxflag = true;
    }
  else{
    rxflag = false;
    }
}
