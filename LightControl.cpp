#include "LightControl.h"

LightControl::LightControl()
:_joyXdata()
,_joyYdata()
,_joySWdata()
,_direction('x')
,_count(0)
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

char LightControl::chkJoyState(){
    LightControl::readJoy();
    if(_joyXdata > 900 || _joyYdata > 900) this->_direction = 'r'; //right
    else if(_joyXdata < 100 || _joyYdata < 100) this->_direction = 'l';  //left
    else this->_direction = 'x';
    return _direction;
}

void LightControl::onRight(){
    digitalWrite(LED_r_Pin,HIGH); delay(500);
    digitalWrite(LED_r_Pin,LOW); delay(500);
    if(_DEBUG) Serial.println("// 우회전 //");
}

void LightControl::onLeft(){
    digitalWrite(LED_l_Pin,HIGH); delay(500);
    digitalWrite(LED_l_Pin,LOW); delay(500);
    if(_DEBUG) Serial.println("// 좌회전 //");
}

void LightControl::offLED(){
    digitalWrite(LED_r_Pin,LOW); digitalWrite(LED_l_Pin,LOW);
    if(_DEBUG) Serial.println(" LED 꺼짐 ");
}

void LightControl::autoRun(){
RIGHT: 
    if(LightControl::chkJoyState() == 'r') {
        for(int i=0;i<5;i++){
            LightControl::onRight();
            if(LightControl::chkJoyState() == 'l') {goto LEFT;}
            else continue;
        }
    }
LEFT:
    if(LightControl::chkJoyState() == 'l') {
        for(int i=0;i<5;i++){
            LightControl::onLeft();
            if(LightControl::chkJoyState() == 'r'){goto RIGHT;} 
            else continue;
        }
    }
}

LightControl::~LightControl()
{
}
