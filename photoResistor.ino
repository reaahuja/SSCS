// Constants
const int pResistor = A1;
const int buzzerPin = 8;  // Pin for the buzzer

// Variables
int value;                // Store value from photoresistor (0-1023)

void setup() {
  pinMode(pResistor, INPUT);     
  pinMode(buzzerPin, OUTPUT);    
  
  Serial.begin(9600);            // Derial communication
}

void loop() {
  value = analogRead(pResistor);  // Read the value from the photoresitor
  value = map(value, 1023, 0, 10, 0);

  if (value == 0) {
    Serial.println("high frequency");
    tone(buzzerPin, 1000);      // High-frequency tone
  }
  else {
    Serial.println("low frequency");
    tone(buzzerPin, 100);       // Low-frequency tone
  }
  
  delay(1000);                   // Small delay
}
