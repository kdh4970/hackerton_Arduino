#include "SliderControl.h"

SliderControl::SliderControl()
:_lockState(false)
,_helmetState(false)
,_Duration1()
,_Duration2()
,_US1(NewPing(trig1_Pin, echo1_Pin, 300))
,_US2(NewPing(trig2_Pin, echo2_Pin, 300))
{
}

void SliderControl::USdebug(){
  delay(50);
  Serial.print("US1 : "); Serial.print(_US1.ping_cm()); Serial.print("cm / ");
  delay(50);
  Serial.print("US2 : "); Serial.print(_US2.ping_cm()); Serial.println("cm");
}

void SliderControl::lock(){
  if(_lockState) return; // 잠금상태 체크
  digitalWrite(motor1Pin,HIGH); digitalWrite(motor2Pin,LOW);
  delay(M_RUNTIME);
  digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,LOW);
  this->_lockState = !_lockState;
  Serial.println("Lock");
}

void SliderControl::unlock(){
  if(!_lockState) return; // 잠금상태 체크
  digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,HIGH);
  delay(M_RUNTIME);
  digitalWrite(motor1Pin,LOW); digitalWrite(motor2Pin,LOW);
  this->_lockState = !_lockState;
  Serial.println("Unlock");
}

void SliderControl::chkHelmet(){
  if(_US1.ping_cm()<10 && _US2.ping_cm()<10) _helmetState=true;
  else _helmetState = false;
}

void SliderControl::autoRun(){
  if(_DEBUG) SliderControl::USdebug();
  SliderControl::chkHelmet();
  if(_helmetState == true && _lockState == true) SliderControl::unlock();
  else if(_helmetState == false && _lockState == false) SliderControl::lock();
}


SliderControl::~SliderControl()
{
}
