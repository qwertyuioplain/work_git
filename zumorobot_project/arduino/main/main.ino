#include <Wire.h>       //無線シリアル通信ライブラリ
#include <ZumoMotors.h> //zumorobotライブラリ
#include <Pushbutton.h> //ホームボタンライブラリ
#include <LSM303.h>     //地磁気センサーライブラリ

//構造体宣言
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
LSM303 compass;

//変数宣言
unsigned long timeNow;
unsigned long timeInit_G, timeNow_G, timePrev_G; //  スタート時間，経過時間, 1回前
int motorR_G, motorL_G;  // 左右のZumoのモータに与える回転力
int mode_G=0;
float mx=0, my=0, mz=0;
float ax=0, ay=0, az=0;
float heading_G = 0;
int direction = 0;//ロボットの方向
int direction_Int = 0;//ロボットの初期の方向
int count = 0;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  setupCompass();
  button.waitForButton();//ホームボタン押されるまで待機
  calibrationCompass();
  button.waitForButton();
  mode_G = 0;
  timeInit_G = millis();
  timePrev_G=0;
}

}

void loop()
{
}




// 通信方式２
void sendData()
{
  static unsigned long timePrev = 0;
  static int inByte = 0;

  // 50msごとにデータ送信（通信方式２），500msデータ送信要求なし-->データ送信．
  if ( inByte == 0 || timeNow_G - timePrev > 500 || (Serial.available() > 0 && timeNow_G - timePrev > 50)) { // 50msごとにデータ送信
    inByte = Serial.read();
    inByte = 1;

    Serial.write('H');
    Serial.write(mode_G);
    Serial.write((int)red_G );
    Serial.write((int)green_G );
    Serial.write((int)blue_G );

    timePrev = timeNow_G;
  }
}
