unsigned long timePrev,time_count = 0;//時間保管変数
int count = 0;//カウント変数
float temp_sum = 0;//温度の合計値
//温度の平均値を返す関数
float average_data(){
    return temp_sum/count;
}
void setup() {
    Serial.begin(9600);
    Serial.println("start!");
    timePrev = millis();//時間を更新
    time_count = millis();//時間を更新
}
void loop() {
    unsigned long timeNow = millis();//時間を更新
    int sensorValue = analogRead(A0);//センサの値を取得
    float vo = sensorValue * (5.0 / 1024.0);//電圧を計算
    float Temp = (vo*1000.0 - 600.0)/10.0;//電圧を温度に変換
    temp_sum += Temp;//温度の加算
    count++;//加算回数を記録
    //100msごとに分岐
    if(timeNow - timePrev >= 100){
        Serial.println(average_data());//平均温度をシリアル通信で表示
        timePrev = timeNow;//時間の更新
        temp_sum = 0;//初期化
        count = 0;//初期化
    }
    //１０秒でシリアル通信を終了する
    if (timeNow - time_count > 10000){
        Serial.println("end!!");
        Serial.end();//シリアル通信終了
    }
}