int val0;
int high0,low0;
unsigned long int timePrev, timeNow;
void setup(){
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
  timePrev = millis(); // 経過時間の初期値
}
void loop(){
  timeNow = millis(); // 現在の経過時間
  val0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  //1バイトに修正
  high0 = val0 >> 8;
  low0 =  val0 & 255;
  if ( timeNow - timePrev >= 50 ) { // 50ms ごとに実行
    Serial.write( 'H' ); // 文字 ’H’ をバイナリデータとして送信
    Serial.write(high0); // 1 バイトのバイナリデータとして値を送信
    Serial.write(low0); // 1 バイトのバイナリデータとして値を送信
    timePrev = timeNow; // 1 ステップ前の経過時間を更新
    Serial.println(val0);
  }
}
