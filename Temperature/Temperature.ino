#include <DHT.h>

// Define the pin where the DHT11 sensor is connected
#define DHTPIN 21     // Digital Pin 2 for the DHT11 sensor
#define DHTTYPE DHT11   // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);    // Initialize serial communication at 9600 bps
  dht.begin();           // Initialize the DHT11 sensor
}

void loop() {
  // Read temperature and humidity values
  float humidity = dht.readHumidity();       // Reading humidity
  float temperature = dht.readTemperature(); // Reading temperature in Celsius

  // Check if any readings failed and exit early to retry
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Wait a few seconds between readings
  delay(2000);  // 2-second delay between readings
}
