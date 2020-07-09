unsigned long timePrev,time_count = 0;
int count = 0;
float temp_sum = 0;

float average_data(){
    return temp_sum/count;
}

void setup() {
    Serial.begin(9600);
    Serial.println("start!");
    timePrev = millis();
    time_count = millis();
}
void loop() {
    unsigned long timeNow = millis();
    int sensorValue = analogRead(A0);
    float vo = sensorValue * (5.0 / 1024.0);
    float Temp = (vo*1000.0 - 600.0)/10.0;
    temp_sum += Temp;
    count++;

    if(timeNow - timePrev >= 100){
        Serial.println(average_data());
        timePrev = timeNow;
        temp_sum = 0;
        count = 0;
    }
    if (timeNow - time_count > 10000){
        Serial.println("end!!");
        Serial.end();
    }
}