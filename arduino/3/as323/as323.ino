float val0;//平均値
int high0,low0;
int time1,time2,time3,time4;
unsigned long int timePrev, timeNow;
long int val0_sum;//出力値の合計
int count;//カウント
void setup(){
    Serial.begin(9600); // シリアル通信を 9600bps で初期化
    timePrev = millis(); // 経過時間の初期値
    count = 0;
}
void loop(){
  timeNow = millis(); // 現在の経過時間
  val0_sum += analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  count++;
  if ( timeNow - timePrev >= 50 ) { // 50ms ごとに実行
    val0 = (float)val0_sum/(float)count;//平均値の計算
    count = 0;//リセット
    val0_sum = 0;//リセット
    //1バイトに修正
    high0 = (int)(val0*100) >> 8;
    low0 =  (int)(val0*100) & 255;
    time1 =(timeNow>>24)&255;
    time2 =(timeNow>>16)&255;
    time3 =(timeNow>>8)&255;
    time4 =timeNow&255;
    Serial.write( 'H' ); // 文字 ’H’ をバイナリデータとして送信
    // 1 バイトのバイナリデータとして値を送信
    Serial.write(time1);
    Serial.write(time2);
    Serial.write(time3);
    Serial.write(time4);
    Serial.write(high0); 
    Serial.write(low0);
    timePrev = timeNow; // 1 ステップ前の経過時間を更新
  }
}
