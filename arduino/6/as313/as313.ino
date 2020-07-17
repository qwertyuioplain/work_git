int val0, val1;
int high0,high1,low0,low1;
unsigned long int timePrev, timeNow;
void setup()
{
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
  timePrev = millis(); // 経過時間の初期値
}
void loop()
{
  timeNow = millis(); // 現在の経過時間
  val0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  val1 = analogRead(1); // A1 ピンの AD 変換結果を取得 (0-1023)
  //1バイトに修正
  high0 = val0 >> 8;
  low0 =  val0 & 255;
  high1 = val1 >> 8;
  low1 =  val1 & 255;
  
  if ( timeNow - timePrev >= 50 ) { // 16ms ごとに実行
    Serial.write( 'H' ); // 文字 ’H’ をバイナリデータとして送信
    Serial.write(high0); // 1 バイトのバイナリデータとして値を送信
    Serial.write(low0); // 1 バイトのバイナリデータとして値を送信
    Serial.write(high1); // 1 バイトのバイナリデータとして値を送信
    Serial.write(low1); // 1 バイトのバイナリデータとして値を送信
    timePrev = timeNow; // 1 ステップ前の経過時間を更新
  }
}
