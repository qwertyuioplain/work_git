int val0,val1;
unsigned long int timeNow,time;
int inByte;
void setup(){
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
  pinMode(13,OUTPUT);//13番ポートを出力
}

void loop(){
  timeNow = millis(); // 現在の経過時間
  val0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  val1 = analogRead(1); // A0 ピンの AD 変換結果を取得 (0-1023)

  if (Serial.available() > 0) {//応答を確認
    inByte = Serial.read();
    digitalWrite(13,HIGH);//13ポートの出力値をHIGH
    delay(50);
    //データ送信
    Serial.write(0x20);
    Serial.write(val0/0x20);
    Serial.write(val0%0x20);
    Serial.write(val1/0x20);
    Serial.write(val1%0x20);
    Serial.write(timeNow>>16);
    Serial.write(timeNow>>8&255);
    Serial.write(timeNow&255);
    time =timeNow;//時間を記録
  }
  else if(timeNow -time>=1000){//応答がない場合
    digitalWrite(13,LOW);//13ポートの出力値をLOW
    Serial.write(0x20);
    Serial.write(val0/0x20);
    Serial.write(val0%0x20);
    Serial.write(val1/0x20);
    Serial.write(val1%0x20);
    Serial.write(timeNow>>16);
    Serial.write(timeNow>>8&255);
    Serial.write(timeNow&255);
  }

}
