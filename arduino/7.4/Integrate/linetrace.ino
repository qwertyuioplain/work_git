void linetrace_bang_bang()
{
  static float lightMin = 80; // 各自で設定
  static float lightMax = 255; // 各自で設定
  static float speed = 80; // パラメーター（各自で設定）
  static float Kp = 0.8; // パラメーター（各自で設定）
  float lightNow;
  float speedDiff;

  lightNow = (red_G + green_G + blue_G ) / 3.0;
  if ( lightNow < (lightMin + lightMax) / 2.0 ) // 右回転
    speedDiff = -Kp * speed;
  else // 左回転
    speedDiff = Kp * speed;
  motorL_G = speed - speedDiff;
  motorR_G = speed + speedDiff;
}


void linetrace_P()
{
  static float lightMin = 85; // 各自で設定
  static float lightMax = 255; // 各自で設定
  static float speed = 100; // パラメーター（各自で設定）
  static float Kp = 1.5; // パラメーター（各自で設定）
  float lightNow;
  float speedDiff;

  lightNow = (red_G + green_G + blue_G ) / 3.0;
  speedDiff = map(lightNow,lightMin,lightMax,-Kp * speed,Kp * speed);
  motorL_G = speed - speedDiff;
  motorR_G = speed + speedDiff;
}

void task_A_pre(){
  switch ( mode_G ) {
    case 0:
      mode_G = 1;
      break;
    case 1:
      linetrace_P(); // ライントレース
      if ( identify_color( 200, 0, 0 ) ) { // 赤かどうか　（引数の値は各自で設定）
        mode_G = 2;
      }
      break;
    case 2:
      motors.setSpeeds(0,0);
      delay(1000);
      mode_G = 3;
      break;
    case 3:
      linetrace_P();
      break;
  }

}

void task_A()
{
  static unsigned long startTime; // static変数，時間計測ははunsigned long
  // この変数は1秒停止の開始時間を覚えておくために使用

  switch ( mode_G ) {
    case 0:
      mode_G = 1;
      break;  // break文を忘れない（忘れるとその下も実行される）

    case 1:
      linetrace_P(); // ライントレース（各自で作成）
      if ( identify_color( 255, 0, 0 ) ) { // 赤かどうか　（引数の値は各自で設定）
        mode_G = 2;
      }
      break;

    // 各自で作成
  }
}


int identify_color( int red, int green, int blue )
{
  float d2;
  float d2_max = 30; // パラメーター（各自で設定）

  d2 = pow(red - red_G, 2) + pow(green - green_G, 2) + pow(blue - blue_G, 2);
  if ( d2 < d2_max * d2_max )
    return 1;
  else
    return 0;
}

int maintainState( unsigned long period )
{
  static int flagStart = 0; // 0:待ち状態，1:現在計測中
  static unsigned long startTime = 0;

  if ( flagStart == 0 ) {
    startTime = timeNow_G; // 計測を開始したtimeNow_Gの値を覚えておく
    flagStart = 1; // 現在計測中にしておく
  }

  if ( timeNow_G - startTime > period ) { // 計測開始からの経過時間が指定時間を越えた
    flagStart = 0; // 待ち状態に戻しておく
    startTime = 0; // なくても良いが，形式的に初期化
    return 1;
  }
  else
    return 0;
}
