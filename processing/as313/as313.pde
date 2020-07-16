import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val0, val1;
int high0,high1,low0,low1;
void setup()
{
  size(1024, 1024); // サイズ 1024× 1024 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
}
void draw()
{
  background(0); // 背景を黒
  ellipse(512, 512, val0, val1); // 中心 (512,512) ,横幅 val0 ,縦幅 val1 の楕円を描
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 5 ) { // 受信バッファに到着しているデータ数が 5 以上なら
    if ( p.read() == 'H' ) { // 読み込んだ 1 バイトが文字 ’H’ なら
      high0 = p.read(); // 受信バッファから 1 バイト読み込み
      low0 = p.read(); // 受信バッファから 1 バイト読み込み
      high1 = p.read(); // 受信バッファから 1 バイト読み込み
      low1 = p.read(); // 受信バッファから 1 バイト読み込み
      val0 = (high0<<8)+low0;
      val1 = (high1<<8)+low1;
      p.clear(); // 念のため受信バッファをクリア
      println("<-");// データ受信タイミング(確認用)
    }
  }
}
