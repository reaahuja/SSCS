#include <Servo.h>
#include <Synth.h>
#include <Ultrasonic.h>

Servo servoMotor;
Synth synth(9);
Ultrasonic ultrasonic(12, 13);

int volumes[3] = { 50, 150, 255 };
// int frequencies[14] = { 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568 };
int frequencies[8] = { 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };


void setup() {
  Serial.begin(115200);
  synth.tone_type(SQUARE_WAVE);
  //pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  servoMotor.attach(10);
}

void loop() {

  int speed = map(analogRead(A1), 0, 1023, 0, 10);
  int startAngle = 0;
  int endAngle = 180;
  int stepSize = 1;
  int delayTime = 15;

  if (speed == 10){
    while(map(analogRead(A1), 0, 1023, 0, 10) == 10){
      for (int angle = startAngle; angle <= endAngle; angle += stepSize) {
        servoMotor.write(angle);
      // stepSize++;
        delay(delayTime);
      }
      for (int angle = endAngle; angle >= startAngle; angle -= stepSize) {
        servoMotor.write(angle);
        //stepSize--;
        delay(delayTime);
      }
    }
  }else if (speed > 0 && speed < 10){
    for (int angle = startAngle; angle <= endAngle; angle += stepSize) {
      servoMotor.write(angle);
      delay(delayTime);
    }
    for (int angle = endAngle; angle >= startAngle; angle -= stepSize) {
      servoMotor.write(angle);
      stepSize--;
      delay(delayTime);
    }
  }else{
    int volRaw = map(analogRead(A0), 0, 1023, 0, 255);
    int fIdxRaw = map(ultrasonic.read(CM), 0, 12, 0, 7);

    int vol = constrain(volRaw, 0, 255);
    int fIdx = constrain(fIdxRaw, 0, 7);
    int freq = frequencies[fIdx];

    synth.tone(freq, vol);
    delay(50);
  }

}



