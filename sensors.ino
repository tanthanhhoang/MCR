byte situation[]={
  0x07 //0b 00 000 111 ->  re phai   0
  ,0x07 //0b 00 000 111 ->  re phai   1
  ,0x0F //0b 00 001 111 ->  re phai   2
  ,0x1F //0b 00 011 111 ->  re phai   3

  ,0x38 //0b 00 111 000 ->  re trai   4
  ,0x38 //0b 00 111 000 ->  re trai   5
  ,0x3C //0b 00 111 100 ->  re trai   6
  ,0x3E //0b 00 111 110 ->  re trai   7

  ,0x1E //0b 00 011 110 ->  cua 90    8
  ,0x3D //0b 00 111 101 ->  cua 90    9
  ,0x2F //0b 00 101 111 ->  cua 90    10
  ,0x3F //0b 00 111 111 ->  cua 90    11
};
void calibrate(int *maxvalue, int *minvalue){
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
  int temp[5],t,timer;
  for(int i=0;i<6;i++){
    minvalue[i]=1024;
    maxvalue[i]=0;
  }
  t=millis();
  while(timer<5000){
    for(int i=0;i<6;i++){
      temp[i]=analogRead(i+14);
      if(temp[i]>maxvalue[i]) maxvalue[i]=temp[i];
      if(temp[i]<minvalue[i]) minvalue[i]=temp[i];
    }
    timer=millis()-t;
  }
}
void rawSensor(int *sensor,int *maxvalue, int *minvalue){//0 5 1 4 2 3
for(int i=5;i>=0;i--){
    sensor[i]=((maxvalue[i]-analogRead(i+14))*56/(maxvalue[i]-minvalue[i]))-20;
    if(sensor[i]<0) sensor[i]=0;
}
}
int transformSensor(int *sensor,int o_out, int *mode){
  int eve,k,maxvalue,maxposition,out;
  eve=0;
  k=0;
  maxvalue=0;
  byte cambien;
  cambien=0x00;
  for(int i=0;i<6;i++){
    if(sensor[i]>17){
      eve+=2*i+1;
      k++;
    }
    if(maxvalue<sensor[i]){
      maxvalue=sensor[i];
      maxposition=i*2+1;
    }
    if(sensor[i]>=15){
      cambien+=(0x01<<i);
    }
  }
  for(int i=0;i<12;i++){
    if(cambien==situation[i]){
      mode[i/4]+=1;
      if(chuyenlan==lineMode){
        return -1;
      }
    }
  }
  if(!((maxposition<=((eve/k)+1))&&(maxposition>=((eve/k)-1)))){
    eve=maxposition*k;
  }
  if(k>0) {
//    if((maxvalue<25)&&(dem!=1)){
//      maximum=19;
//      dem=1;
//    }
    if(decision==cua90){
      if(o_out==-1) return -1;
      else if(o_out==-6) return -6;
    }
    else{
    }
    eve=eve/k;
    out=eve*18;
    if(eve==1){
      if(sensor[1]==0) {
        out-=abs(20-sensor[0]/2);
        if(o_out==216){
          out=216;
        }
        if(out<0) out=0;
        return out;
      }
    }
    if(eve==11){
      if(sensor[4]==0) {
        out+=abs(20-sensor[5]/2);
        if(o_out==0){
          out=0;
        }
        if(out>216) out=216;
        return out;
      }
    }
    for(int i=0;i<6;i++){
      if((i*2+1)<eve){
        out-=sensor[i]/2;
      }
      if((i*2+1)>eve){
        out+=sensor[i]/2;
      }
    }
    if((o_out==216)&&(out<108)){
      out=216;
    }
    if((o_out==0)&&(out>108)){
      out=0;
    }
    return out;
  }
  else if(k==0){
    if(((o_out>=40)&&(o_out<=176))||(o_out==-2)) {
      return -2;
    }
    if(((o_out==-1)||(o_out=-6))&&(chuyenlan==lineMode)) {
      return -6;
    }
    if((o_out<=25)&&(o_out>=0)) {
      return 0;
    }
    if((o_out>=191)&&(o_out<=216)) {
      return 216;
    }
    
  }

}













