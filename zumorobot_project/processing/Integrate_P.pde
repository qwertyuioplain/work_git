
import processing.serial.*;
Serial port; 
int mode;
int green, red, blue, green_p, red_p, blue_p;
int high, low;
int[] sensors = new int[5];
int count;
int[] sensors_p = new int[5];
int count_mode;

void setup() {
  size(1200, 400);
  background(255);
  count = 0;
  println(Serial.list());
  // String arduinoPort = Serial.list()[1];
  // port = new Serial(this, arduinoPort, 9600 );
  // port = new Serial(this, "COM6", 9600 ); // シリアルポート名は各自の環境に合わせて適宜指定
  port = new Serial(this, "/dev/ttyACM0", 9600);
  
  red_p = 0; 
  green_p = 0; 
  blue_p = 0;
  count_mode = 1;
}

void draw() {


  float y_p, y;

  stroke(200, 200, 200);
  line(0, height*0.1, width, height*0.1);
  line(0, height*0.9, width, height*0.9);

  y_p = map(red_p, 0, 255, height*0.9, height*0.1);
  y = map(red, 0, 255, height*0.9, height*0.1);
  stroke(255, 0, 0);
  line((count-1)*10, y_p, (count)*10, y );

  y_p = map(green_p, 0, 255, height*0.9, height*0.1);
  y = map(green, 0, 255, height*0.9, height*0.1);
  stroke(0, 255, 0);
  line((count-1)*10, y_p, (count)*10, y );


  y_p = map(blue_p, 0, 255, height*0.9, height*0.1);
  y = map(blue, 0, 255, height*0.9, height*0.1);
  stroke(0, 0, 255);
  line((count-1)*10, y_p, (count)*10, y );

  stroke(255);
  fill(255);
  rect(0, height-50, 240, 50);
  textSize(50);
  fill(0);
  text("mode=", 20, height-10);
  text((int)mode, 200, height-10);
  noFill();


  if ( count == 120 ) {
    count = 0;
    background(255);
  }
}

void keyPressed() {
  if (key == 's')     
    count_mode = 0;
  else if (key == 'c')
    count_mode = 1;
}


// 通信方式2
void serialEvent(Serial p) { 

  if ( p.available() >= 5 ) { 
    if ( p.read() == 'H' ) {

      red_p = red;
      green_p = green;
      blue_p = blue;

      mode =  p.read();
      red =  p.read();
      green = p.read();
      blue =  p.read();

      p.clear(); // 念のためクリア
      p.write("A");

      print("  RGB = ");
      println(red, green, blue);
      if ( count_mode == 1 )
        ++count;
    }
  }
}
