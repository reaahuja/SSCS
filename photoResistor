// Constants
const int pResistor = A1; 
const int ledPin = 13;  

// Variables
int value;                // Store value from photoresistor (0-1023)

void setup() {
  pinMode(ledPin, OUTPUT);       // Set ledPin - 9 pin as an output
  pinMode(pResistor, INPUT);     // Set pResistor - A0 pin as an input (optional)

  Serial.begin(9600);            // Initialize serial communication
}

void loop() {
  value = analogRead(pResistor);  // Read the value from the photoresistor
  value = map(value, 1023, 0, 10, 0);
  
  Serial.print("Value: ");
  Serial.println(value);
  
  if (value == 0) {
    Serial.println("Turn off");
    digitalWrite(ledPin, LOW);    // Turn led off
  }
  else {
    Serial.println("Turn on");
    digitalWrite(ledPin, HIGH);   // Turn led on
  }

  delay(1000);                     // Small delay
}
