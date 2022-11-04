#ifndef __LIGHT_CONTROL_H__
#define __LIGHT_CONTROL_H__
#include <Arduino.h>
#include "Define.h"

class LightControl
{
private:
    int _joyXdata, _joyYdata, _joySWdata;
    char _direction;
public:
    LightControl();
    ~LightControl();
    void readJoy();
    void chkJoyState();
    void onRight();
    void onLeft();
    void offLED();
    void autoRun();
};

#endif // __LIGHT_CONTROL_H__
