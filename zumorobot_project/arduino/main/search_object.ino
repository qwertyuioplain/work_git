//距離を計測
int distance() {
  unsigned long interval;        //Echoのパルス幅(μs)
  int dist;                      //距離(cm)
  int temp = 23; //温度

  digitalWrite(trig, HIGH);      //10μsのパルスを超音波センサのTrigピンに出力
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  interval = pulseIn(echo, HIGH, 23071);               //Echo信号がHIGHである時間(μs)を計測
  dist = (0.61 * temp + 331.5) * interval / 10000 / 2;   //距離(cm)に変換

  delay(60);                     //trigがHIGHになる間隔を60ms以上空ける（超音波センサの仕様）

  return dist;
}

void search_object() {
  int dist;
  int sum_dist;
  static int t = 0;
  static unsigned long start_time;
  static int prev_dist;

  dist = distance();//距離を計測
  if (dist == 0) {
    dist = prev_dist;
  }
  sum_dist = moving_average(dist);

  switch (mode_G) {
    case 0:
      t++;
      if (t > 5)
        mode_G = 1;
      start_time = timeNow_G;
      break;

    case 1:
      if (timeNow_G - start_time > 2000) {
        mode_G = 2; //物体検知せず,前進
        start_time = timeNow_G;
      }
      else {
        if (sum_dist < 30 && sum_dist > 10) {
          mode_G = 3;//寄せていく
          start_time = timeNow_G;
        }
        else if (prev_dist > sum_dist + 7) {
          mode_G = 5; //その方向へ前進
          start_time = timeNow_G;
        }
        else if (sum_dist >= 2 && sum_dist <= 10) {
          mode_G = 99; //state
        }
        else {
          motorR_G = -130;
          motorL_G = 130;
        }
      }
      break;

    case 2:
      if (timeNow_G - start_time > 1200) {
        mode_G = 1;
        start_time = timeNow_G;
      }
      else {
        motorR_G = 130;
        motorL_G = 130;
      }
      break;

    case 3:
      if (timeNow_G - start_time > 200) { //秒以内なら
        motorL_G = 0;
        motorR_G = 0;
        mode_G = 4;
        start_time = timeNow_G;
      }
      else {
        motorL_G = -100;
        motorR_G = 100;
      }
      break;

    case 4:
      if (sum_dist <= 10 && sum_dist >= 2) {
        motorL_G = 0;
        motorR_G = 0;
        mode_G = 99;
      }
      else if (sum_dist > 10  && sum_dist < 30) {
        motorL_G = 100;
        motorR_G = 100;
      }
      else if (sum_dist > 30) {
        mode_G = 1;
        start_time = timeNow_G;
      }
      break;

    case 5:
      if (timeNow_G - start_time > 200) { //秒以内なら
        motorL_G = 0;
        motorR_G = 0;
        mode_G = 6;
        start_time = timeNow_G;
      }
      else {
        motorL_G = -100;
        motorR_G = 100;
      }
      break;

    case 6:
      if (timeNow_G - start_time > 600) {
        mode_G = 1;
        start_time = timeNow_G;
      }
      else {
        motorR_G = 130;
        motorL_G = 130;
      }
      break;

    case 7:
      motorL_G = 0;
      motorR_G = 0;
      break;

  }
  prev_dist = sum_dist;
}

int moving_average(int x) {
  static int count = 0;
  static int sum = 0;
  static int data[] = {0, 0, 0, 0, 0};

  if (count == 5) {
    count = 0;
  }

  sum -= data[count]; //古い値を削除
  data[count] = x;
  sum += data[count]; //新しい値を追加
  count++;

  return sum / 5; //過去 5 件の移動平均を返す
}
