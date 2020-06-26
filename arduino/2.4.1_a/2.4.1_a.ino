#include <MsTimer2.h>
const int LED1_PIN = 13; // 13 番ピンに LED を接続
const int LED2_PIN = 9; // 9 番ピンに LED を接続
const int change_time = 5000; //発光状態の変化期間
const int time_interval = 20; //割り込み間隔

void flash() {
    // 割り込みサービスルーチン(LED の点滅)
    int val = 255; //PWM波の出力値
    static int time = 0;//時間の初期化
    time += time_interval;//時間の加算
    if (time>=change_time){
        time = 0; //時間の初期化
    }
    val = 255-255*((float)time/change_time);//出力値の計算
    Serial.println(time);
    Serial.println(val);
    analogWrite(LED2_PIN, val); //指定ポートにPWM波を出力
}

void setup() { // 初期設定
    pinMode(LED1_PIN, OUTPUT); // 13 番ピンを出力ポートに設定
    pinMode(LED2_PIN, OUTPUT); // 9 番ピンを出力ポートに設定
    Serial.begin(9600);//シリアル通信を初期化
    MsTimer2::set(time_interval, flash); // タイマ割り込み間隔の設定(T=1000ms)
    MsTimer2::start(); // タイマ割り込み開始
}
void loop() { // ポーリング
    digitalWrite(LED1_PIN, HIGH); // 13 ピンに 5V 出力
    delay(500); // 500ms 待機
    digitalWrite(LED1_PIN, LOW); // 13 ピンに 0V 出力
    delay(500); // 500ms 待機
}