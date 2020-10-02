const int trig = 7; //Trig ピンをデジタル 7 番に接続
const int echo = 8; //Echo ピンをデジタル 8 番に接続
const int temp = 25;//温度
unsigned long interval; //Echo のパルス幅
unsigned int d;//距離
//setup
void setup() {
    Serial.begin(9600);
    pinMode(trig, OUTPUT);//7 番を出力ポートに設定
    pinMode(echo, INPUT);//8 番を入力ポートに設定
}
//音速の計算(m/s)
float sonic_speed_calc(){
    return 0.61*temp+331.5;
}
//距離の計算(m)
float distance_calc(){
    return sonic_speed_calc()*interval/1000000/2;
}
void loop() {
    //10μs のパルスを Tring ピンに出力
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    //Echo 信号が HIGH である時間(μs)を pulseIn 関数で計測
    //23071μs 以上経過したら、超音波が反射して返ってこないとみなして 0 を返す
    interval = pulseIn(echo, HIGH, 23071);//マイクロ秒

    d = (unsigned int)(distance_calc()*100);//cmに変換

    Serial.println(d); //超音波の往復時間をシリアルモニタに表示
    delay(60);//次の Trig 信号の出力まで 60ms 待機
}