const int potPin = A0;    // Analog for the potentiometer
const int buzzerPin = 8;  // Digital for the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  
  Serial.begin(9600);         
}

void loop() {
  int potValue = analogRead(potPin);        // Read the analog value from the potentiometer
  int volume = map(potValue, 0, 1023, 0, 255);  // Map the potentiometer
  
  analogWrite(buzzerPin, volume);  // PMW the buzzer 
  
  Serial.println("Potentiometer Value: ");
  Serial.println(potValue);
  
  delay(1000);  
}
