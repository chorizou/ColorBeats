/*
fht_adc.pde
guest openmusiclabs.com 9.5.12
example sketch for testing the fht library.
it takes in data on ADC0 (Analog0) and processes them
with the fht. the data is sent out over the serial
port at 115.2kb.  there is a pure data patch for
visualizing the data.
*/

#define LOG_OUT 1 // use the log output function
#define FHT_N 256 // set to 256 point fht
const int START_PIN = 2;
const int NUM_PINS = 10;
const int bgNoise = 35; // background noise
const int offset = 280; 
uint8_t lastVol = 0;

const int arr1[] = {9};
const int arr2[] = {3, 10};
const int arr3[] = {5,6, 11};
const int arr4[] = {2, 4, 7, 8};
const int pat[3][10] = {
     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
     {1, 1, 1, 1, 1, 0, 0, 0, 1, 1}     
  };
#include <FHT.h> // include the library
#include <math.h>

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0

  for(int i = START_PIN; i < START_PIN + NUM_PINS; i++)
    pinMode(i, OUTPUT); 
}

void setPins(int arr[], int len) {
  for (int i = 2; i < len+2; i++)
    digitalWrite(i, arr[i-2]);
}

void ripple(int dt) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      setPins(pat[i], 10);
    }
    delay(dt);
  }
  delay(dt);
  for (int i = START_PIN ; i < START_PIN + NUM_PINS; i++)
    digitalWrite(i, 1);
}

void lights(uint8_t hist[], int histSize){
  delayMicroseconds(10);
  uint16_t sum = 0;
  uint8_t max = 1;
  for(int i = 4; i < histSize - 4; i++){
    sum += hist[i];
    if(hist[i] > max)
      max = hist[i];
  }
    
  uint16_t vol =  sum / (FHT_N/2 - 8) * (1000.0/max);
  if(vol > offset)
    vol -= offset;
   else 
    vol = 0;
   if(vol > 255)
    vol = 255;
  Serial.print(sum);
  Serial.print(" ");
  Serial.println(vol);
  /*
  if(abs(vol - lastVol) > bgNoise){
    for(int i = START_PIN; i < START_PIN + NUM_PINS; i++)
      digitalWrite(i, HIGH);
    if(vol > 10)
      analogWrite(arr1[0], 255 - vol);
    if(vol > 50)
      for(int i = 0; i < 2; i++)
        analogWrite(arr2[i], 255 - vol);
    if(vol > 95)
      for(int i = 0; i < 3; i++)
        analogWrite(arr3[i], 255 - vol);
    if(vol > 150)
      for(int i = 0; i < 4; i++)
        analogWrite(arr4[i], 255 - vol);
    delay(800);
        
  }
  */
  if(abs(vol - lastVol) > bgNoise){
    for(int i = START_PIN; i < START_PIN + NUM_PINS; i++)
      digitalWrite(i, HIGH);

     if(vol > 20)
        setPins(pat[0], NUM_PINS);
     if(vol > 70)
        setPins(pat[1], NUM_PINS);
     if(vol > 140)
        setPins(pat[2], NUM_PINS);
     delay(800);
  }
  
  
    
  lastVol = vol;
    
}

void loop() {
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
    lights(fht_log_out, FHT_N/2);
    /*
    for(int i = 4; i < FHT_N / 2; i++){
      //uint8_t out = ;
      Serial.print(fht_log_out[i]); // send out the data
      Serial.print(" ");
    }
    Serial.println();
    */
  }

 
}
