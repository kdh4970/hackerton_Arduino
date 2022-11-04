#ifndef __SLIDER_CONTROL_H__
#define __SLIDER_CONTROL_H__
#include <Arduino.h>
#include <NewPing.h>
#include "Define.h"

class SliderControl
{
private:
    bool _lockState, _helmetState; // 슬라이더 잠금상태, 헬멧 착용 여부
    float _Duration1,_Duration2,filtered_1,filtered_2;
    int _count=10;
public:
    SliderControl();
    ~SliderControl();
    NewPing _US1,_US2;
    void lock(); // 슬라이더 잠금
    void unlock(); // 슬라이더 개방
    void chkHelmet(); // 헬멧 착용여부 확인
    float filter1(int count);
    float filter2(int count);
    void autoRun(); // 헬멧 착용여부 기반 자동 개폐 함수
};


#endif //__SLIDER_CONTROL_H__
