float D = 0.25;//デューティー比を設定
int val;//引数val

void setup() {
    pinMode(9, OUTPUT); //ポート9番を出力ポートに設定
}

void loop() { 
    for (int i = 0; i < 5; i++){
        val = 255*D*i;//valの計算
        analogWrite(9,val);//9番ポートにPWM波を出力
        delay(1000); //一秒の遅延
    }
    delay(1000);//一秒の遅延
}
