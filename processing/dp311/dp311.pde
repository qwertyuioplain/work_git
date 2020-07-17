import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val0;
int high0,low0;
float x,y;//座標
float rad;
void setup()
{
  size(500,500); // サイズ 500×500 のウィンドウ生成
  //座標の初期化
  x = 0;
  y = 0;
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  background(255,255,255); // 背景を白
}
void draw(){
    rad = (2*PI*val0/255)-PI/2;//ラジアン計算
    //座標の設定
    x = 200 +100*cos(rad);
    y = 200 +100*sin(rad);
    background(255,255,255);//背景白
    strokeWeight(3);//先の太さ
    stroke(0);//赤色に設定
    ellipse(200,200,200,200);//円の描写
    stroke(255,0,0);//赤色に設定
    line(200,200, x, y);//線の描写
    println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 2 ) { // 受信バッファに到着しているデータ数が3以上なら
    if ( p.read() == 'H' ) { // 読み込んだ 1 バイトが文字 ’H’ なら
      val0 = p.read(); // 受信バッファから 1 バイト読み込み
      p.clear(); // 念のため受信バッファをクリア
      println("<-");// データ受信タイミング(確認用)
    }
  }
}
