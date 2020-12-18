#include <ZumoMotors.h>           // Zumo用モータ制御ライブラリの読み込み
#include <Pushbutton.h>           // Zumo用ユーザボタンライブラリの読み込み
#include <Wire.h>                 // I2C/TWI 通信デバイスの制御用ライブラリの読み込み
#include <LSM303.h>               // 加速度，地磁気センサ用ライブラリの読み込み
#include "Adafruit_TCS34725.h"    // カラーセンサライブラリのヘッダーファイル

float red_G, green_G, blue_G; // カラーセンサで読み取ったRGB値（0-255）
const int trig = 2;              //TrigピンをArduinoの2番ピンに
const int echo = 4;              //EchoピンをArduinoの4番ピンに
int cnt = 0;                      // 送信回数の確認用カウンタ
int motorR_G, motorL_G; // 左右のZumoのモータに与える回転力
int dist;
float ax=0, ay=0, az=0;


#define CRB_REG_M_2_5GAUSS 0x60   // CRB_REG_M の値 ： 地磁気センサーのスケールを +/-2.5 ガウスに設定
#define CRA_REG_M_220HZ    0x1C   // CRA_REG_M の値 ： 地磁気センサのアップデートレートを 220 Hz に設定

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_60X);
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
LSM303 compass;

//距離を計測
int distance() {
  unsigned long interval;        //Echoのパルス幅(μs)
  int dist;                      //距離(cm)
  
  digitalWrite(trig, HIGH);      //10μsのパルスを超音波センサのTrigピンに出力
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  interval = pulseIn(echo, HIGH, 2307);               //Echo信号がHIGHである時間(μs)を計測
  dist = (0.61 * 25 + 331.5) * interval / 10000 / 2;   //距離(cm)に変換

  delay(60);                     //trigがHIGHになる間隔を60ms以上空ける（超音波センサの仕様）

  return dist;
}


void setup()
{
  Serial.begin(9600);             // シリアル通信の初期化
  Wire.begin();                   // Wireライブラリの初期化と，I2Cバスとの接続
  tcs.begin(); // カラーセンサーのsetup
  pinMode(trig, OUTPUT);         //trigを出力ポートに設定
  pinMode(echo, INPUT);          //echoを入力ポートに設定
  compass.init();                 // LSM303 の初期化
  compass.enableDefault();        // 加速度センサ・地磁気センサ を利用可能にする
  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // 地磁気センサーのスケールを +/-2.5 ガウスに設定
  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ);    // 地磁気センサのアップデートレートを 220 Hz に設定

  button.waitForButton();         // ユーザボタンが押されるまで待つ
}

void loop()
{
  /*地磁気センサー*/
  compass.read();                 // 地磁気センサの値を読む
  Serial.print(compass.m.x);      // 地磁気センサから得られた値(x)をシリアル送信
  Serial.print(",");              // 区切り文字（,）をシリアル送信
  Serial.print(compass.m.y);      // 地磁気センサから得られた値(y)をシリアル送信
  Serial.print(",");              // 区切り文字（,）をシリアル送信
  /*カラーセンサー*/
  tcs.getRGB(red_G, green_G, blue_G); // カラーセンサでRGB値を取得(0-255)
  Serial.print(red_G);
  Serial.print(",");
  Serial.print(green_G);
  Serial.print(",");
  Serial.print(blue_G);
  Serial.print(",");
  /*超音波センサー*/
  dist = distance();
  Serial.print(dist);
  Serial.print(",");
  /*加速度センサー*/
  ax = compass.a.x/256; //map(compass.a.x,-32768,32767,-128,127);
  ay = compass.a.y/256; //map(compass.a.y,-32768,32767,-128,127);
  az = compass.a.z/256; //map(compass.a.z,-32768,32767,-128,127);
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.println(String(cnt));    // 送信回数カウンタをシリアル送信
  cnt += 1;                       // 送信回数カウンタをインクリメント
  delay(100);                     // 100ms 待つ
}
