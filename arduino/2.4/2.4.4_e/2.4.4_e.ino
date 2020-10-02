unsigned long timePrev = 0; // 基準となる時間を格納

void flash() { // LED の点滅処理
    static boolean output = HIGH;
    digitalWrite(13, output); // LED を D13 に出力設定
    output = !output; // HIGH->LOW, LOW->HIGH 反転させる
}

void setup() {
    pinMode(13, OUTPUT); // 13 番ピンを出力ポートに設定
}

void loop() { // millis 関数による時間計測
    unsigned long timeNow = millis(); // millis 関数を用いて現在の時間情報を取得
    if (timeNow - timePrev >= 750) { // 750ms 以上経過
        flash(); // flash 関数の処理を実行
        timePrev = timeNow; // 時間情報の更新
    }else{}
}