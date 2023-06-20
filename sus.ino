#include <Servo.h>

Servo servo;

enum pins{
  buzzPin = 6,
  trigPin = 9,
  echoPin,
  servoPin,
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
    note = distance>10?1000:100*distance;
    return *this;
  }
  int getNote(){
    return note;
  }
  static int note;
};

int Note::note = 1000;

class play{
  public:
  play(){
    servo.writeMicroseconds(2500);
  }
  void play_sound(){
    Note note;
    tone(buzzPin, (++note).getNote());
  }
  ~play(){
    servo.writeMicroseconds(500);
  }
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  
}