float turnTo(float theta_r) {
  float u;
  float KP = 4.0;
  float TIinv = 2/1000.0;

  //heading_G = atan2(my,mx) * 180 / M_PI;//M_PI:円周率,今向いてる方角の角度を取得
  heading_G = averageHeading();//M_PI:円周率,今向いてる方角の角度を取得
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

void section3(){
  float diff;

  if(button.isPressed()){
    mode_G = 0;
    diff = 0;
    count = 0;
    delay(100);
  }

  switch (mode_G){
    case 0://起動初期時点での処理
      mode_G = 1;
      sum_e = 0;
      break;
    case 1://30cm前進
      motorL_G = 150;
      motorR_G = 150;
      if(waitfor(1700)){
        mode_G = 2;
        motorL_G = 0;
        motorR_G = 0;
      }
      break;
    case 2://-90度セット
      motorL_G = 0;
      motorR_G = 0;
      heading_G = averageHeading();
      direction = heading_G -90;
      if(direction<0)direction +=360;
      mode_G = 3;
      break;
    case 3:
      diff = turnTo(direction);
      motorL_G = diff;
      motorR_G = -diff;
      if(abs(direction-averageHeading()<=3){
        mode_G = 1;
        count += 1;
      }
      if(count == 4){
        mode_G = 4;
      }
      break;
    case 4:
      motorL_G = 0;
      motorR_G = 0;
      break;
    default:
      break;
  }
}
