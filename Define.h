#ifndef __DEFINE_H__
#define __DEFINE_H__

// 모터 제어 핀
#define motor1Pin 9
#define motor2Pin 10

// 초음파 센서 핀
#define trig1_Pin 42
#define echo1_Pin 43
#define trig2_Pin 28
#define echo2_Pin 30

// 조이스틱 핀  
#define joyX_Pin 8 // 아날로그
#define joyY_Pin 9 // 아날로그
#define joySW_Pin 48 // 디지털

// LED 핀
//#define LED_Left 
//#define LED_Right

// 루프 타임
#define RUNTIME 300 // 조이스틱 인식 및 초음파 센서 주기(ms)
#define M_RUNTIME 1500 // 모터 회전 시간(ms)

// 디버깅 모드
#define _DEBUG false

#endif //__DEFINE_H__
