import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val0;
int time,time_pre;
int x,y;//座標
void setup(){
  size(800,300); // サイズ 800×300 のウィンドウ生成
  //座標の初期化
  x = 0;
  y = 0;
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  background(255,255,255); // 背景を白
}
void draw(){
    //座標の設定
    x = 800*(time%20000)/20000;
    y = 300 -(300*val0/1023);
    if(time-time_pre > 20000){//画面のリセット
        background(255,255,255); //背景を白
        time_pre = time;
    }
    stroke(255,0,0);//赤色に設定
    strokeWeight(3);//先の太さ
    point(x, y);//点を描写
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 6 ) { // 受信バッファに到着
    if ( p.read() == 0x20 ) { 
      val0 = p.read()*0x20+p.read();//２分割データ
      time = p.read()*256*256+p.read()*256+p.read();//３分割データ
      p.clear(); // 念のため受信バッファをクリア
      println("time:"+time+"val:"+val0);// データ受信タイミング(確認用)
      port.write(0xff);
    }
  }
}
void mousePressed(){ // マ ウ ス ボタ ン が押さ れたら 呼び出さ れる 割り 込み関数
    port.write(0xff); // 最初のデータ 送信要求 ( 任意の 1 バイ ト ) を 送信
}
