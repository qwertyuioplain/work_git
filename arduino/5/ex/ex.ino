#include <MsTimer2.h>
const int D2 = 2; // 外部割込みピンの定義
const int D6 = 6; // PWM 出力ディジタルピンの定義
float dutyH=0.25, dutyL=0.2, duty=dutyL; // duty 変数の定義 . duty 比変更
boolean isHigh=false;
// サンプリング周期 [msec]
int Ts = 40;
int iteration = 0;
unsigned long timep = 0;
volatile float motrpm = 0;
//volatile float motrpmf = 0;
volatile boolean isD2High=false;

void countUp() {
    // 外部割込み (D2) の ISR
    if ((isD2High)&&(digitalRead(D2)==LOW)) {
    // 雑音対策 : 本当に LOW か ?
    unsigned long timen = millis();
    motrpm = 1000.0*60.0/(float)(timen-timep);
    //motrpmf = (3*motrpmf+motrpm)/4.0;
    timep=timen;
    isD2High=false;
    } else if ((!isD2High)&&(digitalRead(D2)==HIGH)) {
    // 本当に HIGH か ?
    isD2High=true;
    }
}

void control() {
    // タイマ割込み (MsTimer2) の ISR
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
        Serial.println((unsigned)motrpm);
    }

void setup() {
    analogWrite(D6,dutyH*255);
    attachInterrupt(0,countUp,CHANGE); // 外部割込みピン :D2
    MsTimer2::set(Ts, control); // 40[msec] ごと
    MsTimer2::start();
    Serial.begin(115200);
}

void loop() {}