#include <MsTimer2.h>
const int D6 = 6;
// PWM 出力ディジタルピンの定義
float dutyH=0.25, dutyL=0.2, duty=dutyL;// duty 変数の定義 . duty 比変更
boolean isHigh=true;
int iteration=0;
int Ts=40; // サンプリング周期 [msec]

void control() { // タイマ割り込み (MsTimer2) の ISR
    iteration++;
    if (iteration>=100) {
        // 4[sec] ごと
        iteration=0;
        if (isHigh) {
            isHigh=false;
            duty = dutyL;
        } else {
            isHigh=true;
            duty = dutyH;
        }
    }
    analogWrite(D6,duty*255);
}
void setup() {
    analogWrite(D6,0);
    MsTimer2::set(Ts, control);
    // 40[msec] ごと
    MsTimer2::start();
}
void loop() {}