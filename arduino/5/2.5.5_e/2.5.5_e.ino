int output = LOW; // LED への出力用
void setup(){
    pinMode(13, OUTPUT); // 13 ピンに LED を出力として設定
    Serial.begin(9600); // シリアル通信開始:転送レート 9600
}
void loop() {
    if (Serial.available() > 0) { // パソコンからデータを受信
        int recv = Serial.read(); // 受信データの読み込み
        output = !output; // output の反転
        Serial.println("I received!"); // パソコンへ応答を返す(送信)
    }
    digitalWrite(13, output); // LED の点灯・消灯
}