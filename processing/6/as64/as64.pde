import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val0,val1;
int d = 0;
void setup(){
  size(600, 200); // サイズ 600 × 200 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
}
void draw(){
  background(255); // 背景
  translate(0,100); //原点
  textSize(40);     //テキストサイズ
  text(d,120,15);   //距離テキスト
  fill(0,0,255);    //青色指定
  rect(200,-20,d*8,40);//棒グラフ
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 3 ) { // 受信バッファに到着しているデータ数が 3 以上なら
    if ( p.read() == 'H' ) { // 読み込んだ 1 バイトが文字 ’H’ なら
      val0 = p.read(); // 受信バッファから 1 バイト読み込み
      val1 = p.read(); // 受信バッファから 1 バイト読み込み
      d = (val0<<8) +val1;
      p.clear(); // 念のため受信バッファをクリア
      port.write('A');//任意の1バイトデータ送信

    }
  }
}

void mousePressed(){//マウスボタンによる割り込み
    port.write('A');//任意の1バイトデータ送信
}