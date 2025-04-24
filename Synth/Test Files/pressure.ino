#define out 1
#define sck 2

void setup() {
  pinMode(out, INPUT);   // Connect HX710 OUT 
  pinMode(sck, OUTPUT);  // Connect HX710 SCK 
  Serial.begin(9600);
}

void loop() {
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

  // display pressure
  Serial.println(result);
}