//******************************************************************************************************* HAM PWM TRAI PHAI
void dongco(int t, int p){
  if(t<0) {
    t=t*-1;
    digitalWrite(A, LOW);// điều khiển động cơ trái đi lùi
    digitalWrite(B, HIGH);// điều khiển động cơ trái đi lùi
  }
  else{
    digitalWrite(A, HIGH);// điều khiển động cơ trái đi tới
    digitalWrite(B, LOW );// điều khiển động cơ trái đi tới
  }
  if(t>=205) t=205;
  if(p<0) {
    p=p*-1;
    digitalWrite(C, LOW);// điều khiển động cơ phải đi tới
    digitalWrite(D, HIGH );// điều khiển động cơ phải đi tới
  }
  else{
    digitalWrite(C, HIGH);// điều khiển động cơ phải đi tới
    digitalWrite(D, LOW );// điều khiển động cơ phải đi tới
  }
  if(p>=205) t=205;
  analogWrite(trai, t);
  analogWrite(phai, p);
}
//******************************************************************************************************* HAM XU LY PID
//void PID(int err, int perr, float P, float D){
  //float Pout,Dout;
  //int U_t;
  //Pout=P*err;
  //Dout=D*(err-perr);
  //U_t=(int)(Pout+Dout);
  //if(U_t>0) dongco(maximum,(maximum-U_t));
  //else dongco((maximum+U_t),maximum);
//}



