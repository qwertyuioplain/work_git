void setup() {
  Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(A0);
    float vo = sensorValue * (5.0 / 1024.0);
    float Temp = (vo*1000.0-600.0)/10.0;
    Serial.println(Temp); 
    delay(100); 
}