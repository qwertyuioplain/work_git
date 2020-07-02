const int LED_PIN = 13; // LED を D13 に接続
volatile int output = LOW; // ディジタル出力の値を格納する変数(初期:“LOW”)

/* 初期設定 */
void setup() {
    pinMode(LED_PIN, OUTPUT); // D13 をディジタル出力に設定
    /*
    外部割り込みの設定
    割り込みに使用するディジタルポートを D2 に設定(1 番目の引数=“0”)
    割り込みサービスルーチン blink 関数を実行(2 番目の引数=関数名)
    (例)割り込み要因としてスイッチの状態が“LOW”のときに発生(3 番目の引数)
    */
    attachInterrupt(0, blink, LOW);
}

/* メイン関数 */
void loop(){
    digitalWrite(LED_PIN, output); // スイッチを押すたびに点灯・消灯を繰り返す
}

/* 割り込みサービスルーチン */
void blink(){ // 割り込みの条件にあわせ LED が点灯・消灯を繰り返す
    output = !output; // ディジタル出力を反転(HIGH→LOW,LOW→HIGH)
}