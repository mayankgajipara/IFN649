// Define the analog pin connected to the soil moisture sensor
#define SOIL_SENSOR_PIN 14  // Analog Pin 14

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600); 

  // Set the soil moisture sensor pin as input
  pinMode(SOIL_SENSOR_PIN, INPUT);
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int soilMoistureValue = analogRead(SOIL_SENSOR_PIN);

  // Convert the analog value (0-1023) to a percentage (0-100%)
  float moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Print the soil moisture value and percentage to the Serial Monitor
  Serial.print("Soil Moisture Analog Value: ");
  Serial.print(soilMoistureValue);
  Serial.print(" | Moisture Percentage: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Wait for 1 second before taking the next reading
  delay(1000);
}
