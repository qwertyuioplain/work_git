import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val0;
int t;
int high0,low0;
float x,y;//座標
void setup()
{
  size(800,300); // サイズ 800×300 のウィンドウ生成
  //座標の初期化座標
  x = 0;
  y = 0;
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  background(255,255,255); // 背景を白
}
void draw(){
    //座標の設定
    x += 1;
    y = 300-map(t,24,31,0,300);
    if(x > 800){//画面のリセット
        x = 0;
        background(255,255,255); //背景を白
    }
    stroke(255,0,0);//赤色に設定
    strokeWeight(3);//先の太さ
    point(x, y);//点を描写
    println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するイン
    if ( p.available() >= 3 ) { // 受信バッファに到着しているデータ数が3以上なら
    if ( p.read() == 'H' ) { // 読み込んだ 1 バイトが文字 ’H’ なら
      high0 = p.read(); // 受信バッファから 1 バイト読み込み
      low0 = p.read(); // 受信バッファから 1 バイト読み込み
      //1バイトを元に修正
      val0 = (high0<<8)+low0;
      t = (val0*5000/1024-600)/10;//温度計算
      p.clear(); // 念のため受信バッファをクリア
      println("<-");// データ受信タイミング(確認用)
    }
  }
}
