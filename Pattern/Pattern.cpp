#include "Arduino.h"
#include "Pattern.h"


//Sets all pins to the pattern in the array
void Pattern:: setPins(int arr[], int len) {
  for (int i = 2; i < len+2; i++)
    digitalWrite(i, arr[i-2]);
}

//Turns all lights on
void Pattern:: allOn(int dt) {
  int pat[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  setPins(pat, 10);
  delay(dt);
}

//Turns all lights off
void Pattern:: allOff(int dt) {
  int pat[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  setPins(pat, 10);
  delay(dt);
}

//Cascade, top to bottom
void Pattern:: cascade(int dt) {
  int pat[4][10] = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Cascade, bottom to top
void Pattern:: cascadeReverse(int dt) {
  int pat[4][10] = {
     {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
     {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
     {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Columns, left to right
void Pattern:: columns(int dt) {
  int pat[4][10] = {
     {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Columns, right to left
void Pattern:: columnsReverse(int dt) {
  int pat[4][10] = {
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
     {1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
     {1, 1, 0, 1, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Lights up one by one from the side
void Pattern:: columnsOne(int dt, int pulse) {
  for (int i = 2; i < 12; i++) {
    digitalWrite(i, 0);
    delay(pulse);
  }
  delay(dt);
  allOff(dt);
}

//Ripples outwards
void Pattern:: ripple(int dt) {
  int pat[3][10] = {
     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
     {0, 1, 1, 1, 1, 1, 0, 0, 0, 1}     
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Ripples outwards and stays
void Pattern:: rippleStay(int dt) {
  int pat[3][10] = {
     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}     
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Ripples inwards
void Pattern:: rippleReverse(int dt) {
  int pat[3][10] = {
     {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
     {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}     
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Ripples inwards and stays
void Pattern:: rippleReverseStay(int dt) {
  int pat[3][10] = {
     {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
     {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}     
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Circles inwards
void Pattern:: circle(int dt, int pulse) {
  int order[] = {0, 2, 5, 9, 8, 7, 6, 3, 1, 4};
  for (int i = 0; i < 10; i++) {
    digitalWrite(i, 0);
    delay(pulse);
    allOff(0);
  }
  delay(dt);
  allOff(dt);
}

//The outer lights rotate
void Pattern:: rotation(int dt, int rot) {
  int pat[3][10] = {
    {1, 1, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0, 1, 1, 0}
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(rot);
  }
  delay(dt);
  allOff(dt);
}

//Random, individual lights blinking
void Pattern:: randBlink(int dt, int pulse) {
  int order[] = {1, 5, 6, 8, 0, 3, 9, 2, 7, 6};
  for (int i = 2; i < 12; i++) {
    digitalWrite(order[i-2], 0);
    delay(pulse);
    allOff(0);
  }
  delay(dt);
  allOff(dt);
}

//Random rows blinking
void Pattern:: randRows(int dt, int pulse) {
  int pat[4][10] = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0}
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(pulse);
  }
  delay(dt);
  allOff(dt);
}

//The top and bottom triangles alternate flashing
void Pattern:: alternate(int dt) {
  int pat[2][10] = {
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  allOff(dt);
}

//Smaller triangles flash within the larger triangle
void Pattern:: triangles(int dt, int pulse) {
  int pat[5][10] = {
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(pulse);
  }
  delay(dt);
  allOff(dt);
}

//Lights stream down the sides of the triangle
void Pattern:: stream(int dt, int pulse) {
  int pat[4][10] = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0}
  };
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(pulse);
  }
  delay(dt);
  allOff(dt);
}

//Lights blink on in a s-shape
void Pattern:: sshape(int dt, int pulse) {
  int order[] = {0, 1, 2, 5, 4, 3, 6, 7, 8, 9};
  for (int i = 2; i < 12; i++) {
    digitalWrite(order[i-2], 0);
    delay(pulse);
    allOff(0);
  }
  delay(dt);
  allOff(dt);
}