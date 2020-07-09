unsigned long timePrev = 0;
int count = 0;
void SendData(){
    int sensorValue = analogRead(A0);
    float vo = sensorValue * (5.0 / 1024.0);
    float Temp = (vo*1000.0 - 600.0)/10.0;
    Serial.println(Temp);
    count++;
}
void setup() {
    Serial.begin(9600);
    Serial.println("start!");
    timePrev = millis();
}
void loop() {
    if(count < 100){
        unsigned long timeNow = millis();
        if(timeNow - timePrev >= 100){
            SendData();
            timePrev = timeNow;
        }else{}
    }else{}
}