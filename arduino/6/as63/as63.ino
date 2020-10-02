const int trig = 7; //Trig ピンをデジタル 7 番に接続
const int echo = 8; //Echo ピンをデジタル 8 番に接続
const int pin1 = 3;//LEDピン
const int pin2 = 9;//ブザーピン
const float d1 = 10;//LED点灯距離
const float d2 = 30;//ブザー距離
unsigned long interval; //Echo のパルス幅
int temp = 25;//温度
float d;//距離


//setup
void setup() {
    Serial.begin(9600);
    pinMode(trig, OUTPUT);//7 番を出力ポートに設定
    pinMode(echo, INPUT);//8 番を入力ポートに設定
    pinMode(pin1,OUTPUT);  //ポート3番を出力ポートに設定する
    pinMode(pin2,OUTPUT);  //ポート3番を出力ポートに設定する
}
//音速の計算(m/s)
float sonic_speed_calc(){
    return 0.61*temp+331.5;
}
//距離の計算(m)
float distance_calc(){
    return sonic_speed_calc()*interval/1000000/2;
}

//条件分岐
int change(float v,float th_val){
  if(v != 0){
      return th_val >= v ? HIGH : LOW;
  }else{
      return LOW;
  }
}

void loop() {
    //10μs のパルスを Tring ピンに出力
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    //Echo 信号が HIGH である時間(μs)を pulseIn 関数で計測
    //23071μs 以上経過したら、超音波が反射して返ってこないとみなして 0 を返す
    interval = pulseIn(echo, HIGH, 23071);//マイクロ秒

    d = distance_calc()*100;//cmに変換

    Serial.println(d); //超音波の往復時間をシリアルモニタに表示 
    
    digitalWrite(pin1,change(d,d1));//LED点灯
    //ブザー音の条件分岐
    if(d <= d2 && d > 0){//d2以内
        tone(pin2,map(d,0,30,1000,100));
    }else if(d > d2){//d2より大きい
        tone(pin2,100);
    }else{//例外
        noTone(pin2);
    }
    
    delay(60);//次の Trig 信号の出力まで 60ms 待機
}