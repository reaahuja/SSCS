#include <Servo.h>

Servo servo;
class Note;

enum pins{ //ignore this part, I am bored of using macros
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
  int duration = pulseIn(echoPin, HIGH); //I think it works
  int cm = (duration/2) / 29.1;
  return cm;
}

int lux(){
  return map(analogRead(pResistor), 1023, 0, 10, 0); //plz figure out how the photo-sensor work :(
}

class Note{
  public:
  Note(){
    int distance = dist();
    int factor = lux?1:2;
    this->note = distance > 20? 1000*factor:300*factor*distance;
  }
  friend void play_note(Note& obj);
  private:
  int note = 100;
};

void play_note(Note& obj){
  if(1/*replace it with condition to turn on the block*/){
    servo.attach(servoPin);
    tone(buzzPin, obj.note);
  }else{
    servo.detach();
    noTone(buzzPin);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(pResistor, INPUT);
  servo.attach(servoPin);
}

void loop() {
  servo.write(0);
  {
    Note object;
    play_note(object);
    }
  servo.write(180);
}
