float val = 2.5;  //閾値を設定

//条件分岐
int change(float v,float th_val){
  return th_val < v ? HIGH : LOW;
}

void setup() {
  Serial.begin(9600);//シリアル通信を初期化
  pinMode(3,OUTPUT);  //ポート3番を出力ポートに設定する
}

void loop() {
  int sensorValue = analogRead(A0); //A0のAD変換結果を取得する
  float v0 = sensorValue*(5.0/1024.0);//ディジタルの値から電圧を計算
  Serial.println(v0);
  digitalWrite(3,change(v0,val));//ポート3の状態を書き換える

  delay(1);        //ループにおける遅延
}