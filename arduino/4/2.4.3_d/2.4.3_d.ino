const int LED_PIN = 13; // LED を D13 に接続
volatile int output = LOW; // ディジタル出力の値を格納する変数(初期:“LOW”)

volatile unsigned long time_now,time_s; //時間の格納変数
const int MODE =LOW;//外部割り込みの要因の設定
const int IN_PIN = 2;//割り込みポート
int sw;//スイッチの状態

/* 初期設定 */
void setup() {
    pinMode(LED_PIN, OUTPUT); // D13 をディジタル出力
    switch (MODE){
    case LOW:
        attachInterrupt(IN_PIN-2, blink,LOW);//外部割り込み関数
    break;
    default:
        attachInterrupt(IN_PIN-2, blink,CHANGE);//外部割り込み関数
    break;
    }
}

/* メイン関数 */
void loop(){
    time_now = millis();//時間取得
    sw = digitalRead(IN_PIN);//スイッチ状態取得
    digitalWrite(LED_PIN, output); // スイッチを押すたびに点灯・消灯を繰り返す
}
//チャタリング回避関数
bool chattering_check(){
    bool r = false;
    if(time_now-time_s>50){ //時間待機
        switch (MODE){  //MODEの違いによる分岐
            case RISING:
                if(sw==LOW){
                    r = true;
                }
            break;
            case FALLING:
                if(sw==HIGH){
                    r = true;
                }
            break;
            case CHANGE:
                r = true;
            break;
            case LOW:
                r = true;
            break;
            default:
            break;
        }
        time_s = time_now;
    }
    return r;
}

/* 割り込みサービスルーチン */
void blink(){ // 割り込みの条件にあわせ LED が点灯・消灯を繰り返す
    if(chattering_check()){
        output = !output; // ディジタル出力を反転(HIGH→LOW,LOW→HIGH)
    }
}