float val = (33.6+1.08)/2;  //閾値を設定

//条件分岐
int lux_threshold(float lux,int th_val){
  return th_val < lux ? HIGH : LOW;
}

void setup() {
  Serial.begin(9600);//シリアル通信を初期化
  pinMode(3,OUTPUT);  //ポート3番を出力ポートに設定する
}

void loop() {
  int sensorValue = analogRead(A0); //A0のAD変換結果を取得する
  float vo = sensorValue*(5.0/1024.0);//ディジタルの値から電圧を計算
  float lo = 222*vo; //照度を計算
  Serial.println(lo); //照度をシリアル表示
  digitalWrite(3,!lux_threshold(lo,val));//ポート3の状態を変更

  delay(1);        //ループにおける遅延
}