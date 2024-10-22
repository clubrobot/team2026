//
// Created by boris on 21/10/2024.
//
#include <Arduino.h>
#include <unity.h>

void setup(){
    delay(2500);
    UNITY_BEGIN();
    //Serial.begin(9600);
}
int i=0;

void func(){
    TEST_ASSERT_MESSAGE(false, "Hello World!");
    delay(100);
}

void loop(){
    RUN_TEST(func);
    if(i++==100){
        UNITY_END();
    }
}