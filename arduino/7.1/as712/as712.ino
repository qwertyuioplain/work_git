#include <ZumoMotors.h>          //モータライブラリの読み込み
#include <Pushbutton.h>          //ボタンライブラリの読み込み

const int trig = 2;              //TrigピンをArduinoの2番ピンに
const int echo = 4;              //EchoピンをArduinoの4番ピンに

ZumoMotors motors;               //ZumoMotorsクラスのインスタンス生成
Pushbutton button(ZUMO_BUTTON);  //Pushbuttonクラスのインスタンスを生成

unsigned long time_now,time_int;　//時間

int mode = 0; //ロボットの動作モード

//距離を計測
int distance() {
  unsigned long interval;        //Echoのパルス幅(μs)
  int dist;                      //距離(cm)
  
  digitalWrite(trig, HIGH);      //10μsのパルスを超音波センサのTrigピンに出力
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  interval = pulseIn(echo, HIGH, 23071);               //Echo信号がHIGHである時間(μs)を計測
  dist = (0.61 * 25 + 331.5) * interval / 10000 / 2;   //距離(cm)に変換

  delay(60);                     //trigがHIGHになる間隔を60ms以上空ける（超音波センサの仕様）

  return dist;
}

void setup() {
  button.waitForButton();        //ユーザボタンが押されるまで待機
  Serial.begin(9600);            //シリアル通信を9600bpsに初期化
  pinMode(trig, OUTPUT);         //trigを出力ポートに設定
  pinMode(echo, INPUT);          //echoを入力ポートに設定
  time_int = millis();
  time_now = 0;
  mode = 0;
}
//指定の時間経過を知らせる関数
int wait_time(int time){
  static unsigned long time_start = 0;//時間計測開始時間
  static int flag  = 0;//分岐フラグ
  switch (flag){//計測分岐
  case 0:
    time_start = time_now;//計測開始による保存
    flag = 1;
    break;
  case 1:
    if(time_now -time_start > time){//時間経過
      flag = 0;
      time_start = 0;
      return 1;
    }
    break;
  default:
    break;
  }
  return 0;
}

void loop() {
  int dist;
  time_now = millis() -time_int;

  dist = distance();             //距離を計測
  Serial.println(dist);          //距離をシリアルモニタに出力
  
  switch (mode){
  case 0://回転検知モード
    if (dist > 0&&dist <= 40) {               //障害物がある場合
      if(wait_time(500)){//正面に向くまで少しだけ回転
        motor.setLeftSpeed(0);
        motor.setRightSpeed(0);
      }
      motor.setLeftSpeed(100);  //右に回転
      motor.setRightSpeed(-100);
    } else if(dist > 40 ) {                   //障害物がない場合右に回転
      motors.setLeftSpeed(100); //右に回転
      motors.setRightSpeed(-100);
      if(wait_time(4000)){//4秒経過しても障害物がない場合移行
        mode = 1;//移動モードに移行
      }
    }
    break;
  case 1://前進モード
    motors.setLeftSpeed(100);//前進
    motors.setRightSpeed(100);
    if(wait_time(2000)){//移動二秒後
      mode = 0; //回転検知モードに移行
    }
    break;
  default:
    break;
  }


}
