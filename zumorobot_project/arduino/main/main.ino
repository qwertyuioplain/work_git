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
void dataUpdate();

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  setupCompass();
  button.waitForButton();//ホームボタン押されるまで待機
  calibrationCompass();//キャリブレーションによる最小値、最大値の取得
  button.waitForButton();//ホームボタン押されるまで待機
  mode_G = 0;
  timePrev_G=0;
  timeInit_G = millis();
}

void loop()
{
  timeUpdate();
  dataUpdate();
  switch (mode_G)
  {
  case 0://起動初期時点での処理
    break;
  case 1:

    break;
  
  default:
    break;
  }


  delay(10);
}


void write1byteint(int x) {
  Serial.write(x+128);
}

void write2byte(int x) {
  Serial.write(x>>8);
  Serial.write(x&255);
}

void dataUpdate(){

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
  Serial.write('H');
  write1byteint((int)ax);
  write1byteint((int)ay);
  write1byteint((int)az);
  write1byteint((int)mx);
  write1byteint((int)my);
  write1byteint((int)mz);
  Serial.write(mode_G);
}

float sum_e = 0;
float turnTo(float theta_r) {
  float u;
  float KP = 4.0;
  float TIinv = 2/1000.0;
  heading_G = atan2(my,mx) * 180 / M_PI;//M_PI:円周率,今向いてる方角の角度を取得
  if (heading_G<0) heading_G += 360;
  float e = theta_r-heading_G;//向いている方角の角度と向きたい方角の角度との差を取得
  if (e<-180) e+=360;
  if (e>180)  e-=360;
  if (abs(e) > 45.0 ) { // |e|>45のときはP制御
    u = KP*e;           // P制御
  } else {              // |e|<=45 の時はPI制御
    sum_e += TIinv*e*(timeNow_G-timePrev_G);
    u = KP*(e+sum_e);   // PI 制御
  }
  if ( u> 180 ) u = 180;  // 飽和
  if ( u<-180 ) u = -180; // 飽和
  return u;
}

int waitfor( unsigned long period )
{
  static int flagStart = 0; // 0:待ち状態, 1:現在計測中
  static unsigned long startTime = 0;

  if ( flagStart == 0 ) {
    startTime = timeNow_G;
    flagStart = 1; // 現在計測中にしておく
  }

  if ( timeNow_G - startTime > period ) { // 計測開始からの経過時間が指定時間を超えた
    flagStart = 0;  // 待ち状態に戻しておく
    startTime = 0;  // なくてもよいが, 形式的に初期化
    return 1;
  }
  return 0;
}

/*
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
  */
