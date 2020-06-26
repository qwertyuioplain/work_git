void setup() {
    pinMode(9, OUTPUT); //ポート9番を出力ポートに設定
}

void loop() {
    int val = 0;
    for (int i = 0; i <= 200; i++){
        if(i <= 100){
            val = 255*0.8*i/100;//valの計算
        }
        else{
            val = 255*0.8*(100-i)/100;
        }
        analogWrite(9,val);//9番ポートにPWM波を出力
        delay(10); //遅延
    }
}