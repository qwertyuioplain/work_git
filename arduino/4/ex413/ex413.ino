int sensorValue0, sensorValue1;
int inByte; // Processing から の送信要求を 受け 取る 変数
void setup(){
    Serial.begin(9600);
}
void loop(){
    sensorValue0 = analogRead(0);
    sensorValue1 = analogRead(1);
    if (Serial.available() > 0) { // 送信要求を 受け 取っ た ( 受信バッ フ ァ に データ あり )
        inByte = Serial.read(); // 受信済みの信号を 読み込む ( 受信バッ フ ァ が空に な る )
        // 本来はこ こ で送信要求の内容を 確認すべき である が, コ ード 簡素化のため省略
        Serial.write(0x20); // SoF:Start of Frame 送信
        Serial.write(sensorValue0 / 0x20);
        Serial.write(sensorValue0 % 0x20);
        Serial.write(sensorValue1 / 0x20);
        Serial.write(sensorValue1 % 0x20);
    }
}