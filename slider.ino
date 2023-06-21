const int potPin = A0;    // Analog input pin for the potentiometer
const int buzzerPin = 8;  // Digital output pin for the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
  Serial.begin(9600);          // Initialize serial communication
}

void loop() {
  int potValue = analogRead(potPin);        // Read the analog value from the potentiometer
  int volume = map(potValue, 0, 1023, 0, 255);  // Map the potentiometer value to a volume range
  
  analogWrite(buzzerPin, volume);  // PMW the buzzer 
  
  Serial.println("Potentiometer Value: ");
  Serial.println(potValue);
  
  delay(1000);  // Small delay between readings
}
