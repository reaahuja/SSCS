//Pins are set with values 
const int potPin = A0;    
const int buzzerPin = 9;  

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
  Serial.begin(9600);          
}

void loop() {
  int potValue = analogRead(potPin);        // Read the analog value from the potentiometer
  int frequency = map(potValue, 0, 1023, 100, 2000);  // Map the potentiometer value to a frequency range
  
  tone(buzzerPin, frequency);  // Play tone on buzzer
  
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(", Frequency: ");
  Serial.println(frequency);
  
  delay(100);  // Small delay
}
