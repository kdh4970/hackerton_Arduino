#include "LightControl.h"

LightControl::LightControl()
:_joyXdata()
,_joyYdata()
,_joySWdata()
,_direction('x')
,_joyState(false)
{
}

void LightControl::readJoy(){
    this->_joyXdata = analogRead(joyX_Pin);
    this->_joyYdata = analogRead(joyY_Pin);
    this->_joySWdata = digitalRead(joySW_Pin);
    if(_DEBUG){
    Serial.print("joyX : "); Serial.print(analogRead(joyX_Pin));
    Serial.print(" / joyY : "); Serial.print(analogRead(joyY_Pin));
    Serial.print(" / joyZ : "); Serial.println(digitalRead(joySW_Pin));
    }
}

void LightControl::chkJoyState(){
    if(_joyXdata > 900 || _joyYdata > 900) {
        this->_direction = 'r';
        this->_joyState = true;
    }
    else if(_joyXdata < 100 || _joyYdata < 100) {
        this->_direction = 'l';
        this->_joyState = true;
    }
    if(_joySWdata == LOW ) {
        this->_direction = 'x';
        this->_joyState = false;
    }
}

void LightControl::onRight(){
    if(_direction != 'r') return;
    Serial.println("// 우회전 //");
    
}

void LightControl::onLeft(){
    if(_direction != 'l') return;
    Serial.println("// 좌회전 //");
}

void LightControl::offLED(){
    Serial.println(" LED 꺼짐 ");
}

void LightControl::autoRun(){
    LightControl::readJoy();
    LightControl::chkJoyState();
    if(_joyState){
        if(_direction == 'r') LightControl::onRight();
        else if(_direction == 'l') LightControl::onLeft();
    }
    else if(!_joyState) LightControl::offLED();
}

LightControl::~LightControl()
{
}
