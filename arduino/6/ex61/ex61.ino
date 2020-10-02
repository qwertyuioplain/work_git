const int trig = 7; //Trig ピンをデジタル 7 番に接続
const int echo = 8; //Echo ピンをデジタル 8 番に接続
unsigned long interval; //Echo のパルス幅
void setup() {
    Serial.begin(9600);
    pinMode(trig, OUTPUT);//7 番を出力ポートに設定
    pinMode(echo, INPUT);//8 番を入力ポートに設定
}
void loop() {
    //10μs のパルスを Tring ピンに出力
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    //Echo 信号が HIGH である時間(μs)を pulseIn 関数で計測
    //23071μs 以上経過したら、超音波が反射して返ってこないとみなして 0 を返す
    interval = pulseIn(echo, HIGH, 23071);
    
    Serial.println(interval); //超音波の往復時間をシリアルモニタに表示
    delay(60);//次の Trig 信号の出力まで 60ms 待機
}