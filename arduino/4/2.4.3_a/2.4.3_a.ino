const int LED_PIN = 9; // LED を D13 に接続
unsigned long time_pre,time_now,time_pass; //時間変数
float val;//PWM波の出力値
const float a = (float)255/3000;//傾きの値
const float b = (float)-255/3000;//傾きの値
volatile float m;//一次関数の傾き
/* 初期設定 */
void setup() {
    Serial.begin(9600);//シリアル通信を初期化
    pinMode(LED_PIN, OUTPUT); // D13 をディジタル出力に設定
    attachInterrupt(0, change, FALLING);//外部割り込み
    m = a;//傾きを初期化
}
/* メイン関数 */
void loop(){
    time_now = millis();//時間の取得
    time_pass = time_now -time_pre;//ループ分経過時間計算
    time_pre = time_now;//時間を保存
    val += m*time_pass;//出力値の加算
    if(val > 255){
        val -= 255;
    }else if(val < 0){
        val += 255;
    }
    Serial.println(val);//シリアルモニタ表示
    analogWrite(LED_PIN,val);//9番ポートにPWM波を出力
}
/* 割り込みサービスルーチン */
void change(){
    //傾きの変更>
    if (m == a){
        m = b;
    }
    else{
        m = a;
    }
}