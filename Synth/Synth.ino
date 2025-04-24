// Teensy Based EWI
// Grant Wang

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Wire.h>
#include <LSM303.h>

#include <Keypad.h>

#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delayline[CHORUS_DELAY_LENGTH];

// Pressure Sensor ports
#define out 1
#define sck 2

#define AMP_SD_PIN 15 

// Potentiometer Values -------------------------------
const int potPin1 = A0;
const int potPin2 = A13;
int potValue1 = 0; 
int currPotVal1 = -1;
double potValue2 = 0;
double currPotVal2 = -1;
// ----------------------------------------------------

// 4x4 Keypad Variables -------------------------------
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Wiring: Rows 40–37, Columns 36–33
byte rowPins[ROWS] = {40, 39, 38, 37}; 
byte colPins[COLS] = {36, 35, 34, 33}; 

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// ----------------------------------------------------


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=194.19998931884766,254.1999855041504
AudioEffectChorus        chorus1;        //xy=368.1999969482422,295.1999969482422
AudioOutputI2S           i2s1;           //xy=619.2000350952148,218.20000076293945
AudioEffectReverb        reverb1;   
AudioConnection          patchCord1(waveform1, chorus1);
AudioConnection          patchCord2(chorus1, reverb1);
AudioConnection          patchCord3(reverb1, 0, i2s1, 0);
AudioConnection          patchCord4(reverb1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=588,480

// GUItool: end automatically generated code

LSM303 compass;
char report[80];

void setup() {
  pinMode(out, INPUT);   // Connect HX710 OUT 
  pinMode(sck, OUTPUT);  // Connect HX710 SCK 
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.unmuteLineout();   
  sgtl5000_1.lineOutLevel(31);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.5);
  waveform1.frequency(440);
  waveform1.pulseWidth(0.15);

  chorus1.begin(delayline, CHORUS_DELAY_LENGTH, 4);
  reverb1.reverbTime(0.1);

  chorus1.voices(3, 8.0, 2.5, 0.8);   // Fine control: voices, delay(ms), depth, freq(Hz)

  pinMode(AMP_SD_PIN, OUTPUT);
  digitalWrite(AMP_SD_PIN, HIGH);
}


void loop() {
  char key = keypad.getKey();
  if (key) {
  switch (key) {
    case '1': // dead
      waveform1.frequency(440);
      break;
    case '2': // A
      waveform1.frequency(440);
      break;
    case '3': // Faulty Keypad
      waveform1.frequency(440);
      break;
    case 'A': // Faulty Keypad
      waveform1.frequency(440);
      break;
    case '4': // G
      waveform1.frequency(783.99);
      break;
    case '5':
      waveform1.frequency(440);
      break;
    case '6': // F
      waveform1.frequency(698.46);
      break;
    case 'B': // E
      waveform1.frequency(659.25);
      break;
    case '7': // G#
      waveform1.frequency(830.61);
      break;
    case '8': // Faulty Keypad
      waveform1.frequency(440);
      break;
    case '9': // F#
      waveform1.frequency(739.99);
      break;
    case 'C': // C#
      waveform1.frequency(554.37);
      break;
    case '*': // D
      waveform1.frequency(587.33);
      break;
    case '0':
      waveform1.frequency(440);
      break;
    case '#': // C
      waveform1.frequency(523.25);
      break;
    case 'D': // B
      waveform1.frequency(493.88);
      break;
  }
  Serial.print("Key pressed: ");
  Serial.println(key);
}

    // wait for the current reading to finish
  while (digitalRead(out)) {}

  // read 24 bits
  long result = 0;
  for (int i = 0; i < 24; i++) {
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
    result = result << 1;
    if (digitalRead(out)) {
      result++;
    }
  }

  // get the 2s compliment
  result = result ^ 0x800000;

  // pulse the clock line 3 times to start the next pressure reading
  for (char i = 0; i < 3; i++) {
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
  }

  float pressure = (result - 840000) * (10.0 / (1240000 - 840000));
  // display pressure
  Serial.println(pressure);

  float targetAmplitude = 0;

  // if threshold met, play note
  if (pressure > 204 | pressure < 180)
  {
    targetAmplitude = 0.05; // * (pressure - 208)/3;    <- scale amplitude
    digitalWrite(AMP_SD_PIN, HIGH);   // enable speaker pin
    waveform1.amplitude(targetAmplitude);
    // sgtl5000_1.volume(1);
  }
  else  // else shutdown the speaker pin
  { 
    digitalWrite(AMP_SD_PIN, LOW);
  }
  Serial.println(pressure); 

  // read potentiometer values

  // Chorus setting
  potValue1 = analogRead(potPin1);
  potValue1 = potValue1 / 100;

  if (potValue1 != currPotVal1)
  {
    currPotVal1 = potValue1;
    chorus1.voices(currPotVal1);
  }

  // Reverb setting
  potValue2 = analogRead(potPin2);  

  if (potValue2 != currPotVal2)
  {
    currPotVal2 = potValue2;
    reverb1.reverbTime(currPotVal2);
  }
}



