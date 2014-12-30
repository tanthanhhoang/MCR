#include <EEPROM.h>
//******************************************************************************************************* DEFINE CHAN DIEU KHIEN
#define A 2 //điều hướng động cơ trai
#define B 3 //điều hướng động cơ trai
#define C 4 //điều hướng động cơ phai
#define D 5 //điều hướng động cơ phai
#define trai 9 //bánh xe bên trái
#define phai 11//bánh xe bên phải
#define lineMode 3
#define cua90  2
#define reTrai 1
#define rePhai 0

int error, pErr, maximum, U_t;
int mx[6], mn[6], data[6], p, op, mode[3];
float Kp, Kd;
int c, t, decision, choose;
int in, daodong, dem, tang, xoay, chuyenlan, cua;

void setup() {
  khoitao();
  xoay = lineMode;
  cua = 0;
  chuyenlan = lineMode;
  tang = 0;
  Serial.begin(9600);
  calibrate(mx, mn);
  Kp = 0.60;
  Kd = 2.07;
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(13, LOW);
  while (digitalRead(12));
  rawSensor(data, mx, mn);
  op = transformSensor(data, 108, mode);
  pErr = 108 - op;
  decision = lineMode;
  dongco(100, 100);
  delay(6);
  dongco(0, 0);
}
void loop() {
  rawSensor(data, mx, mn);
  p = transformSensor(data, op, mode);
  Serial.print(decision); Serial.print("\t"); Serial.print(p); Serial.print("\t"); Serial.print(op); Serial.print("\t");
    for(int i=0;i<6;i++){
      Serial.print(data[i]);
      Serial.print("\t");
    }
  Serial.println();
  if (p == -1) {
    c = 0;
    maximum = 32;
    error = pErr;
    U_t = Kp * error;
    pErr = error;
    dongco(maximum + U_t, maximum - U_t);
  }
  if (p >= 0) {
    error = 108 - p;
    if ((decision == lineMode)) {
      daodong = abs(error - pErr);
      if (daodong > 1) {
        dem = 0;
        digitalWrite(13, LOW);
        tang = 0;
        maximum = 40;
      }
      else {
        tang++;
        digitalWrite(13, HIGH);
        if (tang > 180) {
          maximum += 6;
        }
      }
    }
    else {
      maximum = 38;
    }
    //check đã đi qua line chưa
    if (c < 17) {
      c++;
    }
    // nếu qua rồi thì check biến turn là trái hay phải hay cua 90
    if ((c > 9) && (mode[0] + mode[1] + mode[2] > 3) && (decision == lineMode)) {
      choose = maxp(mode);
      decision = choose;
      mode[0] = 0;
      mode[1] = 0;
      mode[2] = 0;
    }
    if ((xoay == lineMode) || (chuyenlan == lineMode)) {
      U_t = Kp * error + Kd * (error - pErr);
      pErr = error;
      dongco(maximum + U_t, maximum - U_t);
    }
    if (xoay == rePhai) {
      if (error * error < 2500) {
        dongco(0, 0);
        delay(100);
        xoay = lineMode;
        decision==lineMode;
        in = 0;
      }
      dongco(35, 0);
    }
    else if (xoay == reTrai) {
      if (error * error < 2500) {
        dongco(0, 0);
        delay(100);
        xoay = lineMode;
        decision=lineMode;
        in = 0;
      }
      dongco(0, 35);
    }
    if (chuyenlan == rePhai) {
      if(cua==1){
        dongco(40,40);
        if(error<-90){
          cua=2;
        }
      }
      else if(cua==2){
        dongco(0,40);
        if((error*error)<2500){
         dongco(0,0);
         delay(100);
         cua=0;
         decision=lineMode;
         chuyenlan=lineMode;
        }
      }
    }
    else if (chuyenlan == reTrai) {
      if(cua==1){
        dongco(40,40);
        if(error>90){
          cua=2;
        }
      }
      else if(cua==2){
        dongco(40,0);
        if((error*error)<2500){
         dongco(0,0);
         delay(100);
         cua=0;
         decision=lineMode;
         chuyenlan=lineMode;
        }
      }
    }
  }
  if (p == -2) {
    if (decision == rePhai) {
      if (cua == 0) {
        cua = 1;
        chuyenlan = rePhai;
        dongco(40, 0);
        delay(500);
        dongco(0, 0);
        delay(90);
      }
      if (cua == 1) {
        dongco(40, 40);
      }
    }
    else if (decision == reTrai) {
      if (cua == 0) {
        cua = 1;
        chuyenlan = rePhai;
        dongco(0, 40);
        delay(500);
        dongco(0, 0);
        delay(90);
      }
      if (cua == 1) {
        dongco(40, 40);
      }
    }
  }
  if ((p == -6) && (decision == cua90)) {
    if (in == 0) {
      xoay = maxp(mode);
      in = 1;
      mode[0] = 0;
      mode[1] = 0;
      mode[2] = 0;
    }
    if (xoay == rePhai) {
      Serial.println("xoay 2");
      xoay = rePhai;
      dongco(35, 0);
    }
    else if (xoay == reTrai) {
      xoay = reTrai;
      dongco(0, 35);
    }
    decision = lineMode;
  }
  op = p;
  //Serial.println(p);
}


























