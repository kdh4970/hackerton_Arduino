#include "Define.h"
#include "SliderControl.h"
#include "LightControl.h"

bool AUTO = true; // 자동제어 변수
SliderControl SC; // 센서, 모터 제어 객체 생성
LightControl LC; // 조이스틱, LED 제어 객체 생성

void setup(){
    pinMode(motor1Pin,OUTPUT); pinMode(motor2Pin,OUTPUT);
    pinMode(trig1_Pin,OUTPUT); pinMode(echo1_Pin,INPUT);
    pinMode(trig2_Pin,OUTPUT); pinMode(echo2_Pin,INPUT);
    pinMode(joySW_Pin,INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(){
    readCMD();
    if(AUTO){SC.autoRun(); LC.autoRun();} // 자동제어 활성화 
    delay(RUNTIME);
}

void readCMD(){
  char CMD = Serial.read();
  if(CMD == 'a') AUTO = !AUTO; // 자동/수동 제어 토글
  else if(CMD == 's') SC.lock(); // 수동 잠금
  else if(CMD == 'r') SC.unlock(); //수동 개방
}
