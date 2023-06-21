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
  Note& operator++(){
    int distance = dist();
    int factor = dist2()?1:2;
    this->note = distance>20?1000*factor:100*distance*factor;
    return *this;
  }
  int getNote(){
    return this->note;
  }
  void changeVolume(int vol = 0){
    analogWrite(buzzPin, vol);
  }
  private:
  int note;
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
      tone(buzzPin, (++note).getNote());
    }
  }
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(pResistor, INPUT);
  servo.attach(servoPin);
}

int dist2(){
  return map(analogRead(pResistor), 1023, 0, 10, 0);
}

void loop() {
  servo.write(0);
  play test;
  test.play_sound();
  delay(500);
  servo.write(180);
  delay(500);
}
