#include <Synth.h>
#include <Ultrasonic.h>
#include <Servo.h>

Synth synth(9);
Ultrasonic ultrasonic(12, 13);
Servo servoMotor;

int volumes[3] = { 50, 150, 255 };
// int frequencies[14] = { 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568 };
int frequencies[8] = { 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };

void setup() {
  Serial.begin(115200);
  synth.tone_type(SQUARE_WAVE);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
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

  int lightReading = analogRead(A1);
  //lightReading = map(lightReading, 1023, 0, 10, 0);

  int servo_position = 700;
  int speed = 6;
  
  //while(true){ 
  if(servo_position < lightReading){
    servo_position += speed;
  }
  if(servo_position > lightReading){
    servo_position -= speed;
  }
  // if(abs(servo_position - target)<speed){
  //   break;
  // }
  //}
  pwm_out(servo_position);
  

  synth.tone(freq, vol);
  delay(50);
}

void pwm_out(int position) {
  int pulseDuration = map(position, 0, 180, 1000, 2000); 
  servoMotor.writeMicroseconds(pulseDuration); 
}
