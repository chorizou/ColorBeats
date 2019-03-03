/*
 * Pattern.h - Library for flashing LED patterns
 * Created by Charissa Zou, March 2, 2019
 */
#ifndef Pattern_h
#define Pattern_h

#include "Arduino.h"

class Pattern
{
  public:
    void setPins(int arr[], int len);
    void allOn(int dt);
    void allOff(int dt);
    void cascade(int dt);
    void cascadeReverse(int dt);
    void columns(int dt);
    void columnsReverse(int dt);
    void columnsOne(int dt, int pulse);
    void ripple(int dt);
    void rippleStay(int dt);
    void rippleReverse(int dt);
    void rippleReverseStay(int dt);
    void circle(int dt, int pulse);
    void rotation(int dt, int rot);
    void randBlink(int dt, int pulse);
    void randRows(int dt, int pulse);
    void alternate(int dt);
    void triangles(int dt, int pulse);
    void stream(int dt, int pulse);
    void sshape(int dt, int pulse);

  /*private: 
    int _pin;
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _pin5;
    int _pin6;
    int _pin7;
    int _pin8;
    int _pin9;*/
};

#endif