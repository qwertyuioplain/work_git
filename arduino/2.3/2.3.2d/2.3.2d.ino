
//照度をPWM波出力値の変換
int convert(int lux,int lux_min,int lux_max){
  int val = 255*(lux -lux_min)/(lux_max-lux_min);//照度からデューティー比の計算
  //例外を排除
  if (val < 0){
    val = 0;
  }
  if(val > 255){
    val = 255;
  }
  return val;
}

void setup() {
  Serial.begin(9600);//シリアル通信を初期化
  pinMode(3,OUTPUT);  //ポート3番を出力ポートに設定する
}

void loop() {
  int sensorValue = analogRead(A0); //A0のAD変換結果を取得する
  float vo = sensorValue*(5.0/1024.0);//ディジタルの値から電圧を計算
  float lo = 222*vo; //照度を計算
  int val = convert(lo,1,40);//PWM波の出力値を取得
  Serial.println(val); //PWM波の出力値をシリアル表示
  analogWrite(3,val);//ポート3にPWM波を出力

  delay(1);        //ループにおける遅延
}