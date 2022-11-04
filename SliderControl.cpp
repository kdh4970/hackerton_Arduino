#include "SliderControl.h"

SliderControl::SliderControl()
:_lockState(true)
,_helmetState(false)
,_Duration1()
,_Duration2()
,_US1(NewPing(trig1_Pin, echo1_Pin, 200))
,_US2(NewPing(trig2_Pin, echo2_Pin, 200))
,filtered_1(0)
,filtered_2(0)
{
}

void SliderControl::lock(){
  if(_lockState) return; // 잠금상태 체크
  digitalWrite(motorEnPin,HIGH);digitalWrite(motor1Pin,HIGH); digitalWrite(motor2Pin,LOW);
  delay(M_RUNTIME);
  digitalWrite(motorEnPin,LOW);digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,LOW);
  this->_lockState = !_lockState;
  if(_DEBUG) Serial.println("Lock");
}

void SliderControl::unlock(){
  if(!_lockState) return; // 잠금상태 체크
  digitalWrite(motorEnPin,HIGH);digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,HIGH);
  delay(M_RUNTIME);
  digitalWrite(motorEnPin,LOW);digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,LOW);
  this->_lockState = !_lockState;
  if(_DEBUG) Serial.println("Unlock");
}

void SliderControl::chkHelmet(){
  if(_DEBUG) {Serial.print("US1 : "); Serial.print(filter1(_count)); Serial.print("cm / ");}
  if(_DEBUG) {Serial.print("US2 : "); Serial.print(filter2(_count)); Serial.println("cm");}

  if(filter1(_count)<=US_cut && filter2(_count)<=US_cut) _helmetState=true;
  else _helmetState = false;
}

float SliderControl::filter1(int count){ // 초음파 센서 노이즈 필터링
  float sum = 0;
  for(int i=0;i<count;i++){
    sum +=_US1.ping_cm(200); delay(30);
  }
  this->filtered_1 = sum / count;
  return filtered_1;
}

float SliderControl::filter2(int count){ // 초음파 센서 노이즈 필터링
  float sum = 0;
  for(int i=0;i<count;i++){
    sum +=_US2.ping_cm(200); delay(30);
  }
  this->filtered_2 = sum / count;
  return filtered_2;
}

void SliderControl::autoRun(){
  SliderControl::chkHelmet();
  if(_helmetState == true && _lockState == true) SliderControl::unlock();
  else if(_helmetState == false && _lockState == false) SliderControl::lock();
}


SliderControl::~SliderControl()
{
}
