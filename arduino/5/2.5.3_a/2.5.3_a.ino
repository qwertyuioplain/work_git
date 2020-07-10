unsigned long timePrev,time_count = 0;//時間保管変数
int count = 0;//カウント変数
float lo_sum = 0;//の合計値
float lo_max = 35;
float lo_avg;
float val;
//温度の平均値を返す関数
float average_data(){
    return lo_sum/count;
}
void setup() {
    Serial.begin(9600);
    Serial.println("start!");
    pinMode(9,OUTPUT);
    timePrev = millis();//時間を更新
    time_count = millis();//時間を更新
}
void loop() {
    unsigned long timeNow = millis();//時間を更新
    int sensorValue = analogRead(A0);//センサの値を取得
    float vo = sensorValue * (5.0 / 1024.0);//電圧を計算
    float lo = 222*vo; //照度を計算
    lo_sum += lo;//温度の加算
    count++;//加算回数を記録
    //500msごとに分岐
    if(timeNow - timePrev >= 500){
        lo_avg = average_data();
        Serial.println(lo_avg);//平均温度をシリアル通信で表示
        timePrev = timeNow;//時間の更新
        lo_sum = 0;//初期化
        count = 0;//初期化
    }
    val = 255*(lo_avg/35);
    analogWrite(9,val);
    //15秒でシリアル通信を終了する
    if (timeNow - time_count > 15000){
        Serial.println("end!!");
        Serial.end();//シリアル通信終了
    }
}