void setup() {
  Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    float vo = sensorValue * (5.0 / 1024.0);
    Serial.println(vo);
    delay(1); 
}
