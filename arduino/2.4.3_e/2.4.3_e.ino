#include <MsTimer2.h>
const int LED1_PIN = 13; // 13 番ピンに LED を接続
const int LED2_PIN = 9; // 9 番ピンに LED を接続

void flash() {
    // 割り込みサービスルーチン(LED の点滅)
    static boolean output = HIGH; // output の初期状態を HIGH にする
    digitalWrite(LED2_PIN, output); // 9 番ピンに出力(HIGH:5V, LOW:0V)
    output = !output; // HIGH->LOW, LOW->HIGH 反転させる
}

void setup() { // 初期設定
    pinMode(LED1_PIN, OUTPUT); // 13 番ピンを出力ポートに設定
    pinMode(LED2_PIN, OUTPUT); // 9 番ピンを出力ポートに設定
    MsTimer2::set(1000, flash); // タイマ割り込み間隔の設定(T=1000ms)
    MsTimer2::start(); // タイマ割り込み開始
}
void loop() { // ポーリング
    digitalWrite(LED1_PIN, HIGH); // 13 ピンに 5V 出力
    delay(500); // 500ms 待機
    digitalWrite(LED1_PIN, LOW); // 13 ピンに 0V 出力
    delay(500); // 500ms 待機
}