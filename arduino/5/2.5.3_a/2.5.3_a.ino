void setup() {
  Serial.begin(9600);//シリアル通信を初期化
}

void loop() {
  int sensorValue = analogRead(A0); //A0のAD変換結果を取得する
  float vo = sensorValue*(5.0/1024.0);//ディジタルの値から電圧を計算
  float lo = 222*vo; //照度を計算
  Serial.println(lo); //照度をシリアル表示

  delay(1);        //ループにおける遅延
}