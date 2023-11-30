#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <MPU6050.h>
#include <Arduino.h>
#include <TFLI2C.h>  

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 12, 11);

// 'Marilyn Monroe 84x48', 84x48px
const unsigned char epd_bitmap_kisspng_siberian_husky_puppy_face_smiley_clip_art_bone_dog_5abe4a305c2b07 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 
	0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
	0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xfe, 
	0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0x80, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x3f, 
	0xff, 0xe0, 0xc0, 0x00, 0x38, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xe1, 0xe0, 0x00, 0x7c, 
	0x7f, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xe1, 0xe0, 0x00, 0x38, 0x7f, 0xff, 0xe0, 0x00, 0x00, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 
	0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x01, 0xfc, 0x00, 0x3f, 0xff, 0xf0, 0x00, 
	0x00, 0xff, 0xff, 0xc0, 0x01, 0xfc, 0x00, 0x3f, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 
	0x70, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 
	0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x03, 0xf8, 0xff, 
	0x80, 0x00, 0x0f, 0xf9, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x3c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 544)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	epd_bitmap_kisspng_siberian_husky_puppy_face_smiley_clip_art_bone_dog_5abe4a305c2b07
};
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);



#define SERVOMIN  105 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  620 // this is the 'maximum' pulse length count (out of 4096)

#define LFT 0
#define LFF 1
#define LFC 2
#define RFT 3
#define RFF 4
#define RFC 5
#define LRT 6
#define LRF 7
#define LRC 8
#define RRT 9
#define RRF 10
#define RRC 11

#define LFT_D 150
#define LFF_D 55
#define LFC_D 123

#define RFT_D 45
#define RFF_D 115
#define RFC_D 102

#define LRT_D 142
#define LRF_D 80
#define LRC_D 35

#define RRT_D 29
#define RRF_D 110
#define RRC_D 93

TFLI2C tflI2C;
int16_t  tfDist;
int16_t  tfAddr = TFL_DEF_ADR;  

class motor_set{
 private:
    int pin;
    int z_point;
  public:
    void set_pin(int x){
      pin = x;
    }
    int get_pin(){
      return pin;
    }

    void set_point(int x){
      z_point = x;
    }
    int get_point(){
      return z_point;
    }
};

motor_set motor[12];
MPU6050 mpu;
int ivmeX,ivmeY,ivmeZ,gyroX,gyroY,gyroZ;
void setup() {

  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  pwm.begin();
  pwm.setPWMFreq(60);

  motor[0].set_pin(LFT);
  motor[1].set_pin(LFF);
  motor[2].set_pin(LFC);

  motor[3].set_pin(RFT);
  motor[4].set_pin(RFF);
  motor[5].set_pin(RFC);

  motor[6].set_pin(LRT);
  motor[7].set_pin(LRF);
  motor[8].set_pin(LRC);

  motor[9].set_pin(RRT);
  motor[10].set_pin(RRF);
  motor[11].set_pin(RRC);

  motor[0].set_point(LFT_D);
  motor[1].set_point(LFF_D);
  motor[2].set_point(LFC_D);
  motor[3].set_point(RFT_D);
  motor[4].set_point(RFF_D);
  motor[5].set_point(RFC_D);
  motor[6].set_point(LRT_D);
  motor[7].set_point(LRF_D);
  motor[8].set_point(LRC_D);
  motor[9].set_point(RRT_D);
  motor[10].set_point(RRF_D);
  motor[11].set_point(RRC_D);

  allcoxa(3);
  delay(500);
  allfemur(-45);
  delay(500);
  allfronttibia(65);
  delay(500);
  allreirtibia(65);
    Serial.begin(9600);

  //Initialize Display
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(2);

  // you can change the contrast around to adapt the display for the best viewing!
  display.setContrast(57);

  // Clear the buffer.
  display.clearDisplay();

  // Invert Display
  //display.invertDisplay(1);
}

char veri = 's'; 

void loop() {

  //if (Serial.available()) {
    // String receivedData = Serial.readStringUntil('\r');
    // Serial.println("Alınan veri: " + receivedData);

    // if (receivedData.equals("merhaba")) { 
    //   fakestep(RFT, RFF, LRT, LRF);
    //   fakestep(LFT, LFF, RRT, RRF);
    //  

      //dinamik();

      if(tflI2C.getData(tfDist, tfAddr)){

      if(tfDist>15){
        Serial.println(String(tfDist)+" cm / " + String(tfDist/2.54)+" inches");
        fakestep(RFT, RFF, LRT, LRF);
        delay(75);
        fakestep(LFT, LFF, RRT, RRF);
    }
    else{
      allcoxa(0);
      delay(500);
      allfemur(-45);
      delay(500);
      allfronttibia(65);
      delay(500);
      allreirtibia(65);
      }
    delay(50);

   
    // Display bitmap
    display.drawBitmap(0, 0,  epd_bitmap_kisspng_siberian_husky_puppy_face_smiley_clip_art_bone_dog_5abe4a305c2b07, 84, 48, BLACK);
    display.display();
    display.clearDisplay();
    
 }

//  if(tflI2C.getData(tfDist, tfAddr)){
//         Serial.println(String(tfDist)+" cm / " + String(tfDist/2.54)+" inches");
//     }
//     delay(50);


    // kinematik(-8,20);
  
    // kinematik(-1,15.80);
      
    // kinematik(0,16.80);

    // kinematik(2,20);
   

  // elver();
  
}

void calculate_func(){

  int start = -8;
  int stop = 2;

  float y, i;
  for(; start<=stop ;start++){
    y = 0.20 * pow(start+3,2) + 17;
    Serial.println("-------------------------------");
    Serial.println(start);
    Serial.println(y);
  }


}


void elver(){

  swrite(motor[RFT],70);
  swrite(motor[RFF],50);

  delay(1000);

  swrite(motor[RFT],80);
  swrite(motor[RFF],60);

  delay(100);

  
  swrite(motor[RFT],60);
  swrite(motor[RFF],40);


  delay(100);

  swrite(motor[RFT],70);
  swrite(motor[RFF],50);
}
void step(int tb_1, int fm_1,int tb_2, int fm_2, float tibia_Angles, float femur_Angles){

  swrite(motor[tb_1],tibia_Angles);
  swrite(motor[fm_1],femur_Angles);
  delay(100);
  swrite(motor[tb_2],tibia_Angles);
  swrite(motor[fm_2],femur_Angles);

}

void dinamik(){
    double rft = 80;
    double lft = 80;
    double rrt = 80;
    double lrt = 80;
    double rff = -40;
    double lff = -40;
    double rrf = -55;
    double lrf = -55;

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accX = (float)ax / 16384.0;
  float accY = (float)ay / 16384.0;
  float accZ = (float)az / 16384.0;


  int accAngleX = atan(accY / sqrt(pow(accX, 2) + pow(accZ, 2))) * 180 / PI;
  int accAngleY = atan(-1 * accX / sqrt(pow(accY, 2) + pow(accZ, 2))) * 180 / PI;

  Serial.print("Acc X: ");
  Serial.print(accAngleX);
  Serial.print(" | Acc Y: ");
  Serial.println(accAngleY);
  Serial.println("------------------------------------------");

  if((accAngleX%2) == 0){
    swrite(motor[RRT],rrt+(accAngleX));
    swrite(motor[LRT],lrt+(accAngleX));
    swrite(motor[RFT],rft-(accAngleX*1));
    swrite(motor[LFT],lft-(accAngleX*1));
    swrite(motor[RFF],rff+(accAngleX*1));
    swrite(motor[LFF],lff+(accAngleX*1));
  }

  delay(50);

}


void kinematik(float x , float y){
  float a_kenar= 13.1;
  float c_kenar= 10.7;
  float b_kenar, a_aci, b_aci, c_aci, y_aci, z_aci;
  float Tibia_aci, Femur_aci;

  //1. adim

  b_kenar = sqrt(pow(x,2) + pow(y,2));
  Serial.print("B kenar:  ");
  Serial.println(b_kenar);
  //2. adim

  b_aci =( pow(c_kenar,2) + pow(a_kenar,2) - pow(b_kenar,2) ) / (2*c_kenar*a_kenar);
  b_aci = (acos(b_aci))*(180/M_PI);
  Serial.print("B aci:  ");
  Serial.println(b_aci);

  //3.adim

  a_aci = ( pow(b_kenar,2) + pow(c_kenar,2) - pow(a_kenar,2) ) / (2*b_kenar*c_kenar);
  a_aci = acos(a_aci)*(180/M_PI);
  Serial.print("a aci:  ");
  Serial.println(a_aci);

  //4.adim

  y_aci = y / b_kenar;
  y_aci = asin(y_aci)*(180/M_PI);
      Serial.print("y aci:  ");
  Serial.println(y_aci);

 //5.adim
  y_aci = 90-y_aci;
   Serial.println(y_aci);
  //6.adim
  z_aci = (pow(b_kenar,2) + pow(y,2) - pow(x,2)) / (2*b_kenar*y);
  z_aci = acos(z_aci)*(180/M_PI);
  Serial.println(z_aci);

  if(x>=0){
      Femur_aci = a_aci - y_aci;
  } 
  if(x<0){
      Femur_aci = a_aci + z_aci;
  }
  Tibia_aci = b_aci;

  Serial.print("Femur aci:  ");
  Serial.println(Femur_aci);

  Serial.print("Tibia aci:  ");
  Serial.println(180-Tibia_aci);

  step(RFT,RFF,LRT,LRF,180-Tibia_aci,-Femur_aci);

    step(LFT,LFF,RRT,RRF,180-Tibia_aci,-Femur_aci);

}


void swrite(motor_set n1, int degree){

   if(n1.get_pin() == RFT || n1.get_pin() == RFF || n1.get_pin() == RFC || n1.get_pin() == RRT || n1.get_pin() == RRF || n1.get_pin() == RRC){
     pwm.setPWM(n1.get_pin(),0,cv(n1.get_point()+degree));
    }
   if(n1.get_pin() == LFT || n1.get_pin() == LFF || n1.get_pin() == LFC || n1.get_pin() == LRT || n1.get_pin() == LRF || n1.get_pin() == LRC){
     pwm.setPWM(n1.get_pin(),0,cv(n1.get_point()-degree));
    }

}

double cv(int x){
  double degree;
  degree = (double(620-105)/180*x)+105;
  return degree;
}

void allfemur(int degree){
  swrite(motor[LFF],degree);
  swrite(motor[RFF],degree);
  swrite(motor[LRF],degree);
  swrite(motor[RRF],degree);
}
void allcoxa(int degree){
  swrite(motor[LFC],degree);
  swrite(motor[RFC],degree);
  swrite(motor[LRC],degree);
  swrite(motor[RRC],degree);
}
void alltibia(int degree){
  swrite(motor[LFT],degree);
  swrite(motor[RFT],degree);
  swrite(motor[LRT],degree);
  swrite(motor[RRT],degree);
}
void allfrontfemur(int degree){
  swrite(motor[LFF],degree);
  swrite(motor[RFF],degree);
}
void allreirfemur(int degree){
  swrite(motor[LRF],degree);
  swrite(motor[RRF],degree);
}
void allfronttibia(int degree){
  swrite(motor[LFT],degree);
  swrite(motor[RFT],degree);
}
void allreirtibia(int degree){
  swrite(motor[LRT],degree);
  swrite(motor[RRT],degree);
}
void allreircoxa(int degree){
  swrite(motor[LRC],degree);
  swrite(motor[RRC],degree);
}
void allfrontcoxa(int degree){
  swrite(motor[LFC],degree);
  swrite(motor[RFC],degree);
}
void leftcoxas(int degree){
  swrite(motor[LRC],degree);
  swrite(motor[LFC],degree);
}
void rightcoxas(int degree){
  swrite(motor[RRC],degree);
  swrite(motor[RFC],degree);
}
void pos_cal(){

  swrite(motor[LFT],0);
  swrite(motor[LFF],0);
  swrite(motor[LFC],0);
  delay(100);
  swrite(motor[LRT],0);
  swrite(motor[LRF],0);
  swrite(motor[LRC],0);
  delay(100);
  swrite(motor[RFT],0);
  swrite(motor[RFF],0);
  swrite(motor[RFC],0);
  delay(100);
  swrite(motor[RRT],0);
  swrite(motor[RRF],0);
  swrite(motor[RRC],0);

}

void fakestep(int tb_1, int fm_1,int tb_2, int fm_2){

    swrite(motor[fm_1],-60);

    swrite(motor[tb_1],90);

    swrite(motor[fm_2],-60);

    swrite(motor[tb_2],90);

    delay(200);

    swrite(motor[fm_1],-50);

    swrite(motor[tb_1],60);

    swrite(motor[fm_2],-50);

    swrite(motor[tb_2],60);


}
