int val0;
unsigned long int timeNow;
int inByte;
void setup(){
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
}

void loop(){
  timeNow = millis(); // 現在の経過時間
  val0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  if (Serial.available() > 0) {//データ確認
    inByte = Serial.read();
    //データ送信
    Serial.write(0x20);
    Serial.write(val0/0x20);
    Serial.write(val0%0x20);
    Serial.write(timeNow>>16);
    Serial.write(timeNow>>8&255);
    Serial.write(timeNow&255);
  }
}
