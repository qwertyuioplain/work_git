#include <Wire.h>       //無線シリアル通信ライブラリ
#include <ZumoMotors.h> //zumorobotライブラリ
#include <Pushbutton.h> //ホームボタンライブラリ
#include "Adafruit_TCS34725.h"//カラーセンサのヘッダー
#include <LSM303.h>     //地磁気センサーライブラリ

//構造体宣言
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS,TCS34725_GAIN_60X);
LSM303 compass;

//変数宣言
unsigned long timeInit_G, timeNow_G, timePrev_G; //  スタート時間，経過時間, 1回前の経過時間
int motorR_G, motorL_G;  // 左右のZumoのモータに与える回転力
int mode_G=0;

const int trig = 2;
const int echo = 4;
bool search = false;
int mode;

float red_G,green_G,blue_G;//カラーセンサのRGB値

float mx=0, my=0, mz=0;
float ax=0, ay=0, az=0;
float sum_e = 0;
float heading_G = 0;
int direction = 0;//ロボットの方向
int direction_Int = 0;//ロボットの初期の方向
int count = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tcs.begin();//カラーセンサセットアップ
  setupCompass();
  
  button.waitForButton();//ホームボタン押されるまで待機
  calibrationCompass();//キャリブレーションによる最小値、最大値の取得
  button.waitForButton();//ホームボタン押されるまで待機
  
  mode_G = 0;
  count = 0;
  motorL_G = 0;
  motorR_G = 0;
  timePrev_G = 0;
  timeInit_G = millis();
}

void loop()
{
  timeUpdate();
  dataUpdate();
  //section3();
  //colortask();
  //search_object();
  motors.setSpeeds(motorL_G,motorR_G);
  timePrev_G = timeNow_G;
  sendData();
  delay(10);
}


void timeUpdate(){
  timeNow_G = millis() - timeInit_G; // 経過時間
}


void dataUpdate(){

  //地磁気センサーの値を更新
  compass.read();
  compass.m_min.x = min(compass.m.x,compass.m_min.x);  compass.m_max.x = max(compass.m.x,compass.m_max.x);
  compass.m_min.y = min(compass.m.y,compass.m_min.y);  compass.m_max.y = max(compass.m.y,compass.m_max.y);
  compass.m_min.z = min(compass.m.z,compass.m_min.z);  compass.m_max.z = max(compass.m.z,compass.m_max.z);
  ax = compass.a.x/256; map(compass.a.x,-32768,32767,-128,127);
  ay = compass.a.y/256; map(compass.a.y,-32768,32767,-128,127);
  az = compass.a.z/256; map(compass.a.z,-32768,32767,-128,127);
  mx = map(compass.m.x,compass.m_min.x,compass.m_max.x,-128,127);
  my = map(compass.m.y,compass.m_min.y,compass.m_max.y,-128,127);
  mz = map(compass.m.z,compass.m_min.z,compass.m_max.z,-128,127); 
  
  //カラーセンサの値更新
  tcs.getRGB(red_G,green_G,blue_G);

}
