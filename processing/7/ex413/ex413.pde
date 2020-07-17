import processing.serial.*;
Serial port;
int val0, val1;
void setup(){
    size(500, 500);
    port = new Serial(this, "/dev/ttyUSB0", 9600);
}
void draw(){
    background(0);
    int a = (int) map(val0, 0, 1024, 0, width);
    int b = (int) map(val1, 0, 1024, 0, height);
    ellipse(width / 2, height / 2, a, b);
}
void serialEvent(Serial p){
    if (p.available() >= 5) {
        if (p.read() == 0x20) { // SoF:Start of Frame 確認
            val0 = p.read() * 0x20 + p.read();
            val1 = p.read() * 0x20 + p.read();
            println(val0, val1);
            port.write(0xff); // 次のデータ 送信要求 ( 任意の 1 バイ ト ) を 送信
        }
    }
}
void mousePressed(){ // マ ウ ス ボタ ン が押さ れたら 呼び出さ れる 割り 込み関数
    port.write(0xff); // 最初のデータ 送信要求 ( 任意の 1 バイ ト ) を 送信
}