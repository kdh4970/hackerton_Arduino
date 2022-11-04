#ifndef __DEFINE_H__
#define __DEFINE_H__
// 모터 제어 핀
#define motor1Pin 5
#define motor2Pin 6
#define motorEnPin 7

// 초음파 센서 핀
#define trig1_Pin 42
#define echo1_Pin 43
#define trig2_Pin 28
#define echo2_Pin 30

// 조이스틱 핀  
#define joyX_Pin 8 // 아날로그 
#define joyY_Pin 9 // 아날로그
#define joySW_Pin 2 // 디지털, 인터럽트

// LED 핀
#define LED_l_Pin 12
#define LED_r_Pin 13

// 루프 타임
#define M_RUNTIME 1000 // 모터 회전 시간(ms)

// 초음파 판정 거리 
#define US_cut 10

//디버그 모드
extern bool _DEBUG;

#endif //__DEFINE_H__
