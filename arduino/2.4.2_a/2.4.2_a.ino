unsigned long timePrev = 0; // 基準となる時間を格納
const int time_interval = 500;

float input() { //
  int sensorValue = analogRead(A0); //A0のAD変換結果を取得する
  float vo = sensorValue*(5.0/1024.0);//ディジタルの値から電圧を計算
  float lo = 222*vo; //照度を計算
  return lo;
}

void setup() {
  Serial.begin(9600);//シリアル通信を初期化
}

void loop() { // millis 関数による時間計測
    unsigned long timeNow = millis(); // millis 関数を用いて現在の時間情報を取得
    float lo;
    if (timeNow - timePrev >= time_interval) { //
        lo = input();
        timePrev = timeNow; // 時間情報の更新
        Serial.println(lo); //照度をシリアル表示
    }else{}

}