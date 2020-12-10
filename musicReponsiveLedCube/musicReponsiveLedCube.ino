#include <arduinoFFT.h>

#define SOUNDPIN A5 //sound pin attach to
#define SAMPLES 128 //must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz must be less than 10'000 due to ADC

#define LOW_FREQ 21
#define MID_FREQ 42
#define HIGH_FREQ 64

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds; //curr time since the arduino board has started

double vReal[SAMPLES];
double vImag[SAMPLES];

int columns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
int rows[] = {A0, A1, A2, A3, A4};

int row; // Variable for a row
int column; // variable for a column

//setup code (run once):
void setup() {
  Serial.begin(9600); //oder 115200
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  int counter;
  for (int counter = 0; counter < 25; counter++) {
    pinMode(columns[counter], OUTPUT);
  }

  for (int counter = 0; counter < 5; counter++) {
    pinMode(rows[counter], OUTPUT);
  }
}

// main code (run repeatedly):
void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    microseconds = micros(); //overflows after around 70 times
    vReal[i] = analogRead(SOUNDPIN);
    vImag[i] = 0;
    while (micros() < (microseconds + sampling_period_us)) {
    }
  }

  //FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  for (int i = 0; i < (SAMPLES / 2); i++) {
    vReal[i] = sqrt(vReal[i] * vReal[i] + vImag[i] * vImag[i]);

    if (vReal[i] == 0) {
      noFreq();
    } else if (vReal[i] <= LOW_FREQ) {
      lowFreq();
    } else if (vReal[i] <= MID_FREQ) {
      midFreq();
    } else if (vReal[i] <= HIGH_FREQ) {
      highFreq();
    }
  }
}

void visualizeCube() {


}

void noFreq() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(rows[i], HIGH);
    for (int i = 0; i < 25; i++) {
    digitalWrite(columns[i], LOW);
  }
  }
  
}


void lowFreq() {
  digitalWrite(rows[0], HIGH);
  digitalWrite(rows[1], HIGH);
  digitalWrite(rows[2], LOW);
  digitalWrite(rows[3], HIGH);
  digitalWrite(rows[4], HIGH);
  for (int i = 0; i < 25; i++) {
    digitalWrite(columns[i], LOW);
  }
  digitalWrite(columns[12], HIGH);
}

void midFreq() {
  digitalWrite(rows[0], HIGH);
  digitalWrite(rows[4], HIGH);
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[1], LOW);
    digitalWrite(rows[2], LOW);
    digitalWrite(rows[3], LOW);
    digitalWrite(columns[i], LOW);
  }
  digitalWrite(columns[6], HIGH);
  digitalWrite(columns[7], HIGH);
  digitalWrite(columns[8], HIGH);
  digitalWrite(columns[11], HIGH);
  digitalWrite(columns[12], HIGH);
  digitalWrite(columns[13], HIGH);
  digitalWrite(columns[16], HIGH);
  digitalWrite(columns[17], HIGH);
  digitalWrite(columns[18], HIGH);
}

void highFreq() {
  digitalWrite(rows[0], LOW);
  digitalWrite(rows[1], LOW);
  digitalWrite(rows[2], LOW);
  digitalWrite(rows[3], LOW);
  digitalWrite(rows[4], LOW);
  for (int i = 0; i < 25; i++) {
    digitalWrite(columns[i], HIGH);
  }
}
