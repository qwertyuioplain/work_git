int days = 0;
void setup(){
    Serial.begin(9600); // シリアル通信開始:転送レート 9600
}
void loop() {
    if (Serial.available() > 0) { // パソコンからデータを受信
        int recv = Serial.read(); // 受信データの読み込み
        Serial.println(recv);
        if(recv>=48&&recv<=57){//数字のみ検出
            days = days*10;
            days +=  recv -48;//誕生日を右詰めで取得
        }else if(recv==10){ //データ送信での最後の処理
            Serial.println(days/100+(days-days/100*100));//誕生日と誕生月の加算
            days = 0;
        }else{
        }
    }
}