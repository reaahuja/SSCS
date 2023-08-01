#include <Servo.h>
#include <Synth.h>
#include <Ultrasonic.h>

// Servo servoMotor;
Synth synth(9);
Ultrasonic ultrasonic(12, 13);

// int volumes[3] = { 50, 150, 255 };
int frequencies[8] = { 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };
// int frequencies[14] = { 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568 };

int servoAngle = 0;
int servoForward = true;

void setup() {
  Serial.begin(115200);
  synth.tone_type(SQUARE_WAVE);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  // servoMotor.attach(3);
}

void loop() {
  int lightRaw = analogRead(A1);
  int volRaw = map(analogRead(A0), 0, 1023, 0, 1023);
  int fIdxRaw = map((long) ultrasonic.timing(), 30, 2600, 0, 7);

  if (volRaw < 300) volRaw = 0;
  bool light = lightRaw > 300;
  // int freqRaw = map((long) ultrasonic.timing(), 30, 2600, 900, 2100);
  // int freq = constrain(freqRaw, 900, 2100);
  // int fIdxRaw = map(ultrasonic.read(CM), 0, 20, 0, 7);

  int fIdx = constrain(fIdxRaw, 0, 7);
  int freq = frequencies[fIdx];
  int vol = constrain(volRaw, 0, 1023);

  if (light) {
    synth.stop();

    // Custom servo code required bc synth is not compatible with Servo
    delay(100);
    digitalWrite(3, HIGH);
    delayMicroseconds(servoForward ? 1250 : 1750);
    digitalWrite(3, LOW);

    servoForward = !servoForward;
  }
  else {
    synth.tone(freq, vol);
  }
  
  delay(50);
}
