#include <Servo.h>

Servo servo;

enum pins{
  buzzPin = 6,
  trigPin = 9,
  echoPin,
  servoPin,
  potPin = 14,
  pResistor = 16
};

int dist(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  int duration = pulseIn(echoPin, HIGH);
  int cm = (duration/2) / 29.1;
  return cm;
}

class Note{
  public:
  void calibration(){
    int distance = dist();
    int factor = dist2()?1:2;
    this->note = distance > 20?1000*factor:100*distance*factor;
    Serial.println(this->note);
  }

  int getNote(){
    return this->note;
  }

  void changeVolume(int vol = 0){
    analogWrite(buzzPin, vol);
  }
  private:
  int note = 1000;
};

class play{
  public:
  void play_sound(){
    Note note;
    if(map(analogRead(potPin), 0, 1023, 0, 255) == 255){
      noTone(buzzPin);
      servo.detach();
    }
    else{
      servo.attach(servoPin);
      note.changeVolume(map(analogRead(potPin), 0, 1023, 0, 255));
      note.calibration();
      tone(buzzPin, note.getNote());
    }
  }
};

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(pResistor, INPUT);
  servo.attach(servoPin);
}

int dist2(){
  int temp = map(analogRead(pResistor), 1023, 0, 10, 0);
  if(temp < 4)
    return 0;
  return 1;
}

void loop() {
  servo.write(0);
  play test;
  test.play_sound();
  delay(500);
  servo.write(180);
  delay(500);
}
