#include "DHT.h"

#define SOIL_SENSOR_PIN 14  // Analog Pin 14 for the soil moisture sensor
#define BUZZER_PIN 15       // Digital Pin 15 for the buzzer
#define DHTPIN 21           // Pin 21 for the DHT11 temperature sensor
#define DHTTYPE DHT11       // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

unsigned long previousMillis = 0;  // Variable to store the last time the sensor was checked
const long interval = 3000;        // 2 seconds interval for sensor check

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Setup pins
  pinMode(SOIL_SENSOR_PIN, INPUT);  // Soil moisture sensor
  pinMode(BUZZER_PIN, OUTPUT);      // Buzzer
  dht.begin();                      // Start DHT11 sensor
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 2 seconds have passed since the last sensor check
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time the sensor was checked

    // Read soil moisture
    int soilMoistureValue = analogRead(SOIL_SENSOR_PIN);
    float moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

    // Read temperature
    float temperature = dht.readTemperature();

    // Display the readings
    Serial.print("Soil Moisture: ");
    Serial.print(moisturePercentage);
    Serial.print("% | Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Combined logic for both soil and temperature conditions (emergency)
    if (moisturePercentage < 10 && temperature > 30) {
      // Both soil is too dry and temperature is too high - Emergency beep pattern
      Serial.println("Emergency! Both soil is too dry and temperature is too high!");
      
      // Rapid emergency beeping
      for (int i = 0; i < 10; i++) {  // Loop to create a rapid beep pattern
        tone(BUZZER_PIN, 1000);       // 1 kHz tone
        delay(100);                   // Beep for 100 ms
        noTone(BUZZER_PIN);           // Stop sound
        delay(100);                   // Short interval between beeps
      }
    } 
    else if (moisturePercentage < 10) {
      // Soil is too dry, use a high-pitched tone
      Serial.println("Soil is too dry!");
      tone(BUZZER_PIN, 1000);  // 1 kHz tone for dry soil
      delay(100);              // Beep for 100 ms
      noTone(BUZZER_PIN);      // Stop sound
    } 
    else if (moisturePercentage >= 10 && moisturePercentage < 60) {
      // Moderate moisture, use a short beep
      Serial.println("Moderate soil moisture.");
      tone(BUZZER_PIN, 500);   // 500 Hz tone for moderate soil
      delay(100);              // Beep for 100 ms
      noTone(BUZZER_PIN);      // Stop sound
    } 
    else if (temperature > 30) {
      // If only the temperature is too high (> 30°C), use a different tone
      Serial.println("Temperature is too high!");
      tone(BUZZER_PIN, 200);  // 1.5 kHz tone for high temperature
      delay(200);              // Beep for 200 ms
      noTone(BUZZER_PIN);      // Stop sound
    } 
    else {
      // Soil is moist enough and temperature is okay, turn off buzzer
      Serial.println("Conditions are normal.");
      noTone(BUZZER_PIN);  // Ensure the buzzer is off
    }
  }

  // The rest of the loop continues without delay
}
