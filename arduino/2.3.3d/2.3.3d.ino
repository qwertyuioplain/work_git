void setup() {
    pinMode(9, OUTPUT); //ポート9番を出力ポートに設定
}

void loop() { 
    for (int i = 0; i <= 100; i++){
        int val = 255*i/100;//valの計算
        analogWrite(9,val);//9番ポートにPWM波を出力
        delay(10); //遅延
    }
}