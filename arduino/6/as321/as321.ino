int val0, val1;
void setup(){
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
}
void loop(){
  val0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  val1 = analogRead(1); // A1 ピンの AD 変換結果を取得 (0-1023)
  if ( Serial.available() > 0 ) { //シリアル通信による送信要求を受取時
    val0 = val0 / 4; // 0-255 の値に変換
    val1 = val1 / 4; // 0-255 の値に変換
    Serial.write( 'H' ); // 文字 ’H’ をバイナリデータとして送信
    Serial.write(val0); // 1 バイトのバイナリデータとして値を送信
    Serial.write(val1); // 1 バイトのバイナリデータとして値を送信
  }
}
