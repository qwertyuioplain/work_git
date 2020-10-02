int xn = 20; // 分割数
int x;
size(800, 120);
background(255); // 背景を白
stroke(0); // 線の色を黒
line(0, 0, width, 0);
// 格子の横線を引く
line(0, height, width, height); // 格子の横線を引く
for ( int i = 0; i <= xn; i++ ) { // 格子の縦線を引く
x = i* width/xn; // 線の x 座標
line(x, 0, x, height);
}
stroke(255, 0, 0); // 線の色を赤
for ( int i_c = 0; i_c < xn; i_c++ ) { // i_c はマス目のインデックス
x = width/(2*xn) + i_c*width/xn; // 楕円の中心の x 座標( y 座標は height/2 )
ellipse(x, height/2, width/xn, height); // マス目内に楕円を描く
}