#include <Synth.h>
#include <Ultrasonic.h>
#include <Servo.h>

Synth synth(9);
Ultrasonic ultrasonic(12, 13);
Servo servoMotor;

int volumes[3] = { 50, 150, 255 };
// int frequencies[14] = { 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568 };
int frequencies[8] = { 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };
int photoResistor = A1; 
int lightReading; 

void setup() {
  Serial.begin(115200);
  synth.tone_type(SQUARE_WAVE);
  pinMode(A0, INPUT);
  pinMode(photoResistor, INPUT);
  servoMotor.attach(9);
}

void loop() {
  // int freq, vol;
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 8; j++) {
  //     vol = volumes[i];
  //     freq = frequencies[j];

  //     Serial.print(freq);
  //     Serial.print(" Hz ");
  //     Serial.println(vol);

  //     synth.tone(freq, vol);
  //     delay(100);
  //   }
  //   synth.stop();
  //   delay(500);
  // }
  // synth.stop();
  // delay(1000);
  int volRaw = map(analogRead(A0), 0, 1023, 0, 255);
  int fIdxRaw = map(ultrasonic.read(CM), 0, 12, 0, 7);

  int vol = constrain(volRaw, 0, 255);
  int fIdx = constrain(fIdxRaw, 0, 7);
  int freq = frequencies[fIdx];

  Serial.print(freq);
  Serial.print(" Hz ");
  Serial.println(vol);

  lightReading = analogRead(photoResistor);
  lightReading = map(lightReading, 1023, 0, 1, 0);
  if (value == 1){
    servoMotor.write(180);
    delay(50);
  }
  servoMotor.write(0);
  


  synth.tone(freq, vol);
  delay(50);
}
