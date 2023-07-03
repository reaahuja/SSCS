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
  pinMode(A0, INPUT);
  servoMotor.attach(10);
}

void loop() {
  int servo_position = 1500; 
  int target = 500;
  int speed = analogRead(A1);

  
  while (true) {
    if (servo_position < target) {
      servo_position += speed;
    } 
    if (servo_position > target) {
      servo_position -= speed;
    }
    if (abs(servo_position - target) < speed) {
      break;
    }
    pwm_out(servo_position);

    int volRaw = map(analogRead(A0), 0, 1023, 0, 255);
    int fIdxRaw = map(ultrasonic.read(CM), 0, 12, 0, 7);

    int vol = constrain(volRaw, 0, 255);
    int fIdx = constrain(fIdxRaw, 0, 7);
    int freq = frequencies[fIdx];

    synth.tone(freq, vol);  
    delay(50);
  }
}

void pwm_out(int position) {
  servoMotor.writeMicroseconds(position);
}
