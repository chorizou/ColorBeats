#include <Pattern.h>


#define LOG_OUT 1 // use the log output function
#define FHT_N 64 // set to 256 point fht


#include <FHT.h> // include the library


const int totalT = 4;
int freqIndex = 0;
int8_t allFreq[4][FHT_N/2];

int c = 1000;

int Sensor = A0;
int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
void preprocessHistogram(int histo[]);
void setup() {
  freqIndex = 0;
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  
  pinMode(Sensor, INPUT); //BW
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  for(int i = 0; i < totalT; i++) {
    for(int j = 0; j < FHT_N/2; j++) {
      allFreq[i][j] = 0;
    }
  }
  while(1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < FHT_N ; i++) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fht_input[i] = k; // put real data into bins
    }
    fht_window(); // window the data for better frequency response
    fht_reorder(); // reorder the data before doing the fht
    fht_run(); // process the data in the fht
    fht_mag_log(); // take the output of the fht
    sei();
  //  Serial.println(255); // send a start byte
    for(int i = 0; i < FHT_N / 2; i++) {
      Serial.print(fht_log_out[i]);
      Serial.print(" ");
    }
    Serial.println();

    int histo[FHT_N / 2];
    histo[0] = 255;
    for(int i = 1; i < FHT_N / 2; i++) {
      histo[i] = fht_log_out[i];
    }    
    preprocessHistogram(histo);
    Serial.println("freqindex:");
    Serial.println(freqIndex);
    if(freqIndex >= totalT-1) {
      Serial.println("HELLO");
      preprocessFinish();
      freqIndex = 0;
      for(int i = 0; i < totalT; i++) {
        for(int j = 0; j < FHT_N/2; j++) {
          allFreq[i][j] = 0;
        }
      }
    }

  }

  
}

void drawLevel(int level, int dt) {
  Pattern patt;
  if(level == 4) {
    int arr4[] = {0,0,0,0,0,0,0,0,0,0};
    patt.setPins(arr4, 10);
  }
  if(level == 3) {
    int arr3[] = {0,0,0,0,0,0,1,1,1,1};
    patt.setPins(arr3, 10);
  }
  if(level == 2) {
    int arr2[] = {0,0,0,1,1,1,1,1,1,1};
    patt.setPins(arr2, 10);
  }
  if(level == 1) {
    int arr1[] = {0,1,1,1,1,1,1,1,1,1};
    patt.setPins(arr1, 10);
  }
  if(level == 0) {
    patt.allOff(dt);
  }
  delay(dt);
}

void drawLevel2(int level, int dt) {
  Pattern patt;
  if(level == 1) {
    patt.allOn(dt);
  }
  if(level == 1) {
    patt.cascade(dt);
  }
  if(level == 2) {
    patt.cascadeReverse(dt);
  }
  if(level == 3) {
    patt.columns(dt);
  }
  if(level == 4) {
    patt.columnsReverse(dt);
  }
  if(level == 5) {
    patt.columnsOne(0, dt);
  }
  if(level == 6) {
    patt.ripple(dt);
  }
  if(level == 7) {
    patt.rippleStay(dt);
  }
  if(level == 8) {
    patt.rippleReverse(dt);
  }
  if(level == 9) {
    patt.rippleReverseStay(dt);
  }
  if(level == 10) {
    patt.circle(0,dt);
  }
  if(level == 11) {
    patt.rotation(0,dt);
  }
  if(level == 12) {
    patt.randBlink(0,dt);
  }
  if(level == 13) {
    patt.randRows(0,dt);
  }
  if(level == 14) {
    patt.alternate(dt);
  }
  if(level == 15) {
    patt.triangles(0,dt);
  }
  if(level == 16) {
    patt.stream(0,dt);
  }
  if(level == 17) {
    patt.sshape(0, dt);
  }
  delay(dt);
}

void discoMode(int dt, int rot) {
  Pattern patt;
  int pat[15][10] = {
    {1, 1, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0, 1, 1, 0},
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 1},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 1},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 10; j++) {
      patt.setPins(pat[i], 10);
    }
    delay(rot);
  }
  delay(dt);
  patt.allOff(dt);
}



void loop3() {
  // put your main code here, to run repeatedly:
  
 Pattern patt;
 patt.allOff(1000);
// int c = 1000;
// patt.rotation(c*c, c*c);
//  int status_sensor = analogRead(Sensor);
  
// if(status_sensor > 80) {
//    patt.cascade(20);
//    patt.cascadeReverse(20);
 //   discoMode(0,470*c);
//   ponpokorin(0, 200);

//    int rand = random(1,17);
//    drawLevel2(rand, 300);
//  } 

/*  if (status_sensor <= 30)
  {
    if(clap == 0) {
      patt.allOff(20);
      detection_range_start = detection_range = millis();
    }
    else {
      if(millis()-detection_range >= 50) {
        clap--;
        drawLevel(clap, 50);
        detection_range = millis();
      }
    }
  }
  else {
    clap++;
    drawLevel(clap, 200);

    if(clap == 4) {
      drawLevel(3, 200);
      clap--;
    }

    if(clap == 1) {
      detection_range_start = detection_range = millis();
    }
    else {
      detection_range = millis();
    }
  } */
}


//Called every second or so after song starts and BUTTON pushed

void preprocessHistogram(int histo[FHT_N/2]) {
  for(int i = 0; i < FHT_N/2; i++) {
    allFreq[freqIndex][i] = histo[i];
  }
  freqIndex++;
}

// qsort requires you to create a sort function
int sort_desc(const void *cmp1, const void *cmp2)
{
  // Need to cast the void * to int *
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  // The comparison
  return a > b ? -1 : (a < b ? 1 : 0);
  // A simpler, probably faster way:
  //return b - a;
}

//Called after BUTTON pushed second time, finish preprocessing
//Assume not consecutive data, but like every 5th or so
void preprocessFinish() {
  Serial.println("A");
  int8_t full[totalT * (FHT_N/2-5)];
  int index = 0;
  for(int i = 0; i < totalT; i++) {
    for(int j = 5; j < FHT_N/2; j++) {
      full[index] = allFreq[i][j];
      index++;
    }
  }

Serial.println("B");
  
  int full2[totalT*(FHT_N/2-5)];
  for(int i = 0; i < totalT * (FHT_N/2-5); i++) {
    full2[i] = full[i];
  }
  //Arrays.sort(full);
  int full_length = sizeof(full2) / sizeof(full2[0]);
  qsort(full2, full_length, sizeof(full2[0]), sort_desc);
  int threshold = full2[(int) (0.2 * totalT*(FHT_N/2-5)) ];
  bool above[totalT][FHT_N/2];
  index = 0;
  
  for(int i = 0; i < totalT; i++) {
    for(int j = 5; j < FHT_N/2; j++) {
      if(full[index++] >= threshold) {
        above[i][j] = true;
      }
    }
  }

  Serial.println("threshold");
  Serial.println(threshold);

  index = 0;
  int numTrue = 20;
  for(int i = 5; i < FHT_N/2 && (index == 0); i++) {
    int count = 0;
    for(int j = 0; j < totalT; j++) {
      if(above[j][i])
        count++;
    }

    if(count >= numTrue) {
      index = i;  
    }
  }

  int firstBeat = 0;
  int firstSpace = 0;
  int secondBeat = 0;
  int col = 0;
  while(!above[index][col]) col++;

  int max = 0;
  int maxIndex1 = 0;
  for(int i = col; above[index][i]; i++) {
    if(allFreq[index][i] > max) {
      max = allFreq[index][i];
      maxIndex1 = i;
    }
  }
  
  firstBeat = col;
  while(above[index][col]) col++;
  firstSpace = col;
  while(!above[index][col]) col++;
  secondBeat = col;

  max = 0;
  int maxIndex2 = 0;
  for(int i = col; above[index][i]; i++) {
    if(allFreq[index][i] > max) {
      max = allFreq[index][i];
      maxIndex2 = i;
    }
  }
  
  
  int beatLength = firstSpace - firstBeat;


  
  uint8_t melo[totalT];
  index = 0;

  for(int i = 0; i < totalT; i++) {
    int j = FHT_N/2-1;
    while(!above[i][j]) j--;
    melo[index++] = j;
  }

  Pattern pattern;

  int skip = 2;
  for(int i = 0; i < 2; i++) {
    if((melo[i] == melo[i+1*skip]) && (melo[i+1*skip] == melo[i+2*skip]) && (melo[i+2*skip] == melo[i+3*skip])) {
      pattern.ripple(c*c);
      Serial.print("OPT1");
    }
    if((melo[i] <= melo[i+1*skip]) && (melo[i+1*skip] <= melo[i+2*skip]) && (melo[i+2*skip] <= melo[i+3*skip])) {
      pattern.cascade(c*c);
      Serial.println("OPT2");
    }
    else if((melo[i+3*skip] >= melo[i+2*skip]) && (melo[i+2*skip] >= melo[i+1*skip]) && (melo[i+1*skip] >= melo[i])) {
      pattern.cascadeReverse(c*c);
      Serial.println("OPT3");
    }
    if(melo[i] <= melo[i] || melo[i] >= melo[i]) {
      Serial.println("THIS BETTER WORK");
    }
  }
}
