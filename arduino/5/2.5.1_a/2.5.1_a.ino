int output1 = LOW; // LED への出力用
int output2 = LOW; // LED への出力用

void setup(){
    pinMode(9, OUTPUT); // ９ピンに LED を出力として設定
    pinMode(13, OUTPUT); // 13ピンに LED を出力として設定
    Serial.begin(9600); // シリアル通信開始:転送レート 9600
}
void loop() {
    if (Serial.available() > 0) { // パソコンからデータを受信
        
        int recv = Serial.read(); // 受信データの読み込み
        Serial.println(recv); // パソコンへ応答を返す(送信)
        if (recv<32){//文字数字のASCIIコード以外
        }else if (recv == 48){//0のコードのとき
            output1 = LOW;
            output2 = HIGH;
        }else if(recv == 49){//1のコードのとき
            output1 = HIGH;
            output2 = LOW;
        }else{              //それ以外のコードの時
            output1 = HIGH;
            output2 = HIGH;
        }
        
    }
    digitalWrite(9, output1); // LED の点灯・消灯
    digitalWrite(13, output2); // LED の点灯・消灯
}