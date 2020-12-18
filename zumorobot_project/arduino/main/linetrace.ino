void linetrace_bang_bang()
{
  static float lightMin = 90; // 各自で設定
  static float lightMax = 255; // 各自で設定
  static float speed = 100; // パラメーター（各自で設定）
  static float Kp = 2.0; // パラメーター（各自で設定）
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

void colortask()
{
  static unsigned long startTime; // static変数，時間計測ははunsigned long
  // この変数は1秒停止の開始時間を覚えておくために使用

  if(button.isPressed() ){
    mode_G = 0;
    motors.setSpeeds(0, 0);
    delay(200);
    button.waitForButton();
  }

  switch ( mode_G ) {
    case 0:
      mode_G = 1;
      break;  // break文を忘れない（忘れるとその下も実行される）

    case 1:
      motorL_G = 100;
      motorR_G = 100;
      if ( identify_color( 184, 69, 75 ) || identify_color(47, 96, 165)) { // 赤かどうか　（引数の値は各自で設定）
        mode_G = 2;
      }else if (identify_color(62, 85, 83)){//黒の場合
        mode_G = 4;
      }else if (identify_color(255,255,255)){//白の場合
        mode_G = 1;
      }
      break;

    case 2:
      motorL_G = 0;
      motorR_G = 0;
      if(waitfor(1000)){
        mode_G = 3;
      } 
      break;
    case 3:
      motorL_G = 100;
      motorR_G = 100;
      if (identify_color(62, 85, 83)){//黒の場合
        mode_G = 4;
      }else if(identify_color(255,255,255)){
        mode_G = 1;
      }
      break;
    
    case 4:
      motorL_G = 150;
      motorR_G = -150;
      if(waitfor(random(1000, 1700))) {
        mode_G = 1;
      }
    break;
  }
}


int identify_color( int red, int green, int blue )
{
  float d2;
  float d2_max = 20; // パラメーター（各自で設定）

  d2 = pow(red - red_G, 2) + pow(green - green_G, 2) + pow(blue - blue_G, 2);
  if ( d2 < d2_max * d2_max )
    return 1;
  else
    return 0;
}