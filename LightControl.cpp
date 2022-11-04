#include "LightControl.h"

LightControl::LightControl()
:_joyXdata()
,_joyYdata()
,_joySWdata()
,_direction('x')
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
        this->_direction = 'r'; //right
    }
    else if(_joyXdata < 100 || _joyYdata < 100) {
        this->_direction = 'l'; //left
    }
}

void LightControl::onRight(){
    if(_direction != 'r') return;
    for (int i = 1;i<=5;i++){
        digitalWrite(LED_r_Pin,HIGH); delay(500);
        digitalWrite(LED_r_Pin,LOW); delay(500);
    }
    if(_DEBUG) Serial.println("// 우회전 //");
}

void LightControl::onLeft(){
    if(_direction != 'l') return;
    for (int i = 1;i<=5;i++){
        digitalWrite(LED_l_Pin,HIGH); delay(500);
        digitalWrite(LED_l_Pin,LOW); delay(500);
    }
    if(_DEBUG) Serial.println("// 좌회전 //");
}

void LightControl::offLED(){
    digitalWrite(LED_r_Pin,LOW); digitalWrite(LED_l_Pin,LOW);
    if(_DEBUG) Serial.println(" LED 꺼짐 ");
}

void LightControl::autoRun(){
    LightControl::readJoy();
    LightControl::chkJoyState();
    if(_direction == 'r') {LightControl::onRight(); this->_direction = 'x';}
    else if(_direction == 'l') {LightControl::onLeft(); this->_direction = 'x';}
    else LightControl::offLED();

}

LightControl::~LightControl()
{
}
