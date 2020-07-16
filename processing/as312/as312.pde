int xn = 20; // 分割数
int i_c;
// 楕円を描くマス目番号
void setup(){
    size(800, 120);
    frameRate(60); // フレームレートのデフォルト値は 60
    i_c = 0;
}
void draw(){
    
    int x;
    background(255); // 背景を白
    stroke(0); // 線の色を黒
    line(0, 0, width, 0);
    // 格子の横線を描く
    line(0, height, width, height); // 格子の横線を描く
    for ( int i = 0; i <= xn; i++ ) { // 格子の縦線を描く
        x = i* width/xn; // 線の x 座標
        line(x, 0, x, height);
    }
    // 楕円を描くマス目番号の更新
    i_c++;
    if ( i_c == xn ){
        i_c = 0;
    }
    stroke(255, 0, 0); // 線の色を赤
    x = width/(2*xn) + i_c*width/xn; // 楕円の中心の x 座標( y 座標は height/2 )
    ellipse(x, height/2, width/xn, height); // マス目内に楕円を描く 
}