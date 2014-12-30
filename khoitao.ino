void khoitao(){
  maximum=40;
  pinMode(13, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(trai, OUTPUT);
  pinMode(phai, OUTPUT);
  digitalWrite(A, HIGH);// điều khiển động cơ trái đi tới
  digitalWrite(B, LOW );// điều khiển động cơ trái đi tới
  digitalWrite(C, HIGH);// điều khiển động cơ phải đi tới
  digitalWrite(D, LOW );// điều khiển động cơ phải đi tới
}
int maxp(int *number){
  int r;
  int max_temp=number[2];
  r=2;
  if(number[1]>max_temp) {
    max_temp=number[1];
    r=1;
  }
  if(number[0]>max_temp) 
    r=0;
  return r;
}

