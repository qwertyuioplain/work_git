import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
float val0;//温度のディジタル値
float t;//温度
int high0,low0;
long time = 0;//時間
long time_pre =0;//リセット時刻
int time_max = 10000;//横幅の時間
int time1,time2,time3,time4;
float x,y;//座標
int t_max = 32;//グラフ縦幅の温度最大値
int t_low = 25;//グラフ縦幅の温度最小値
void setup(){
  size(800,300); // サイズ 800×300 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  background(255,255,255); // 背景を白
}
void draw(){
    if(time>time_pre){
        if((time-time_pre)>time_max){//画面のリセット
            time_pre = time;
            background(255,255,255); //背景を白
        }
    }else{//例外を除去
        time_pre = 0;
    }
    //座標の設定
    x = 800*(time%time_max)/time_max;
    y = 300-map(t,t_low,t_max,0,300);
    stroke(255,0,0);//赤色に設定
    strokeWeight(3);//先の太さ
    point(x, y);//点を描写
    println("R"); // 描画タイミング(確認用)
    println(time_pre);
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 7 ) { // 受信バッファに到着しているデータ数が3以上なら
    if ( p.read() == 'H' ) { // 読み込んだ 1 バイトが文字 ’H’ なら
      // 受信バッファから 1 バイト読み込み
      time1 = p.read();
      time2 = p.read();
      time3 = p.read();
      time4 = p.read();
      high0 = p.read();
      low0 = p.read();
      //1バイトを元に修正
      time = (time1<<24)+(time2<<16)+(time3<<8)+time4;
      val0 = (float)((high0<<8)+low0)/100;
      t = (val0*5000/1024-600)/10;//温度計算
      p.clear(); // 念のため受信バッファをクリア
      println("<-");// データ受信タイミング(確認用)
      println(time);
    }
  }
}
