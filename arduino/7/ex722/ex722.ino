
#include <Wire.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <LSM303.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
LSM303 compass;

unsigned long timeInit_G, timeNow_G, timePrev_G; //  スタート時間，経過時間, 1回前
int motorR_G, motorL_G;  // 左右のZumoのモータに与える回転力
int mode_G=0;
float mx=0, my=0, mz=0;//各方向の磁気センサの値
float ax=0, ay=0, az=0;//各方向の加速度の値

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  setupCompass();//キャリブレーションセットアップ
  compass.m_min.x = 32767;  compass.m_min.y = 32767;  compass.m_min.z = 32767;
  compass.m_max.x = -32768;  compass.m_max.y = -32768;  compass.m_max.z = -32768;
  button.waitForButton();//ボタン押すまで待機
  calibrationCompass();//compassファイルの実行
  button.waitForButton();//ボタン押すまで待機
  mode_G = 0;//初期化
  timeInit_G = millis();//初期時間の取得
  timePrev_G=0;//初期化
}

void loop()
{
  timeNow_G = millis() - timeInit_G; // 経過時間

  if (timeNow_G-timePrev_G<100) {//ループ分の今と前の時間差が100ミリ秒以下の場合、例外発生
    return;
  }

  compass.read();//磁気と加速データ取得
  compass.m_min.x = min(compass.m.x,compass.m_min.x);  compass.m_max.x = max(compass.m.x,compass.m_max.x);
  compass.m_min.y = min(compass.m.y,compass.m_min.y);  compass.m_max.y = max(compass.m.y,compass.m_max.y);
  compass.m_min.z = min(compass.m.z,compass.m_min.z);  compass.m_max.z = max(compass.m.z,compass.m_max.z);
  ax = compass.a.x/256; map(compass.a.x,-32768,32767,-128,127);
  ay = compass.a.y/256; map(compass.a.y,-32768,32767,-128,127);
  az = compass.a.z/256; map(compass.a.z,-32768,32767,-128,127);
  mx = map(compass.m.x,compass.m_min.x,compass.m_max.x,-128,127);
  my = map(compass.m.y,compass.m_min.y,compass.m_max.y,-128,127);
  mz = map(compass.m.z,compass.m_min.z,compass.m_max.z,-128,127); 
  sendData(); // データ送信

  timePrev_G=timeNow_G;//時間記録
}

void write1byteint(int x) {//１ビット分書き込み
  Serial.write(x+128);
}

void write2byte(int x) {//２ビット分書き込み
  Serial.write(x>>8);
  Serial.write(x&255);
}

void sendData()
{
    Serial.write('H');
    write1byteint((int)ax);    write1byteint((int)ay);    write1byteint((int)az);
    write1byteint((int)mx);    write1byteint((int)my);    write1byteint((int)mz);
    Serial.write(mode_G);
}
