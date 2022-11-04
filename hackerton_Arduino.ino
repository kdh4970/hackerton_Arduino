#include "Define.h"
#include "SliderControl.h"
#include "LightControl.h"

volatile bool is_emergency = false; // 인터럽트 스위치 변수
bool AUTO = true; // 자동제어 변수
SliderControl SC; // 센서, 모터 제어 객체 생성
LightControl LC; // 조이스틱, LED 제어 객체 생성

void setup(){
    _DEBUG= true;
    setPinMode(); // 핀 입출력 지정
    attachInterrupt(0,emergency,RISING); // 비상깜빡이 인터럽트
    if(_DEBUG) Serial.begin(9600);
}

void loop(){
    readCMD();
    if(is_emergency){
      digitalWrite(LED_l_Pin,HIGH); digitalWrite(LED_r_Pin,HIGH); delay(300);
      digitalWrite(LED_l_Pin,LOW); digitalWrite(LED_r_Pin,LOW); delay(300);
    }
    if(AUTO&&is_emergency==false){SC.autoRun(); LC.autoRun();} // 자동제어 활성화 
}

void setPinMode(){
  pinMode(motorEnPin,OUTPUT); pinMode(motor1Pin,OUTPUT); pinMode(motor2Pin,OUTPUT);
  pinMode(trig1_Pin,OUTPUT); pinMode(echo1_Pin,INPUT);
  pinMode(trig2_Pin,OUTPUT); pinMode(echo2_Pin,INPUT);
  pinMode(joySW_Pin,INPUT_PULLUP);
  pinMode(LED_l_Pin,OUTPUT);pinMode(LED_r_Pin,OUTPUT);
}

void readCMD(){
  char CMD = Serial.read();
  if(CMD == 'a') AUTO = !AUTO; // 자동/수동 제어 토글
  else if(CMD == 's') SC.lock(); // 수동 잠금
  else if(CMD == 'r') SC.unlock(); //수동 개방
  else if(CMD == 'd') {
    Serial.println("------- Debug Toggled -------");
    _DEBUG = !_DEBUG; // 디버그 토글
  }
}

void emergency(){
  is_emergency = !is_emergency;
  digitalWrite(LED_l_Pin,LOW); digitalWrite(LED_r_Pin,LOW);
}
