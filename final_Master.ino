#include <SoftwareSerial.h>
SoftwareSerial LoraMaster(8, 3);// RX | TX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(500);
  LoraMaster.begin(19200);
  LoraMaster.setTimeout(500);
  receive_data();
}
void loop() {
}
void receive_data() {
  // put your main code here, to run repeatedly:
  String rxData;
  char rxByte, state = 0;
  while (1) {
    
    String rxData;
    char rxByte, state = 0;
    int strlength = 0;
    LoraMaster.listen();
    delay(50);
    LoraMaster.println("AT+SEND=0,5,00");
    delay(8000);
    if (LoraMaster.available()) {//receive second
      rxData = CollectData();//接收pH回傳的資料
      Serial.println("send");
      Serial.println(rxData);
      strlength = rxData.length();
    }
    if (strlength > 130)
      break;
  }
}
String CollectData() {//蒐集資料
  String rxData;
  char rxByte;
  while (LoraMaster.available()) {//當有資料時進行動作
    rxByte = LoraMaster.read();//讀取1byte放入rxByte
    rxData += rxByte;//將每個byte合起來
  }
  //  Serial.println(rxData);
  return rxData;//回傳收到的資料
}
