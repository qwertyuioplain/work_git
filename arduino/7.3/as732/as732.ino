#include <ZumoMotors.h>           // Zumo用モータ制御ライブラリの読み込み
#include <Pushbutton.h>           // Zumo用ユーザボタンライブラリの読み込み

unsigned long int timeStart1 = 0;  // 時間計測用変数
unsigned long int timeStart2 = 0;  // 時間計測用変数
unsigned long int timeEnd1 = 0;    // 時間計測用変数
unsigned long int timeEnd2 = 0;    // 時間計測用変数

Pushbutton button(ZUMO_BUTTON);

void setup()
{
  Serial.begin(9600);             // シリアル通信の初期化

  button.waitForButton();         // ユーザボタンが押されるまで待つ
  Serial.println("START");        // 文字列をシリアル送信
}

void loop()
{
  button.waitForButton();         // ユーザボタンが押されるまで待つ
  Serial.println("write");
  timeStart1 = millis();           // 現在の時間取得
  timeStart2 = micros();

  //計測内容
  Serial.write("abcdefg");

  timeEnd1 = millis();             // 現在の時間取得
  timeEnd2 = micros();

  delay(50);                      // 50ms待つ
  Serial.println();
  Serial.println(timeEnd1-timeStart1);    // 経過時間をシリアル送信
  Serial.println(timeEnd2-timeStart2);    // 経過時間をシリアル送信


  button.waitForButton();         // ユーザボタンが押されるまで待つ
  Serial.println("println");
  timeStart1 = millis();           // 現在の時間取得
  timeStart2 = micros();

  //計測内容
  Serial.println("abcdefg");        

  timeEnd1 = millis();             // 現在の時間取得
  timeEnd2 = micros();
  delay(50);                      // 50ms待つ
  Serial.println(timeEnd1-timeStart1);    // 経過時間をシリアル送信
  Serial.println(timeEnd2-timeStart2);    // 経過時間をシリアル送信
}
