#include <DHT.h>

// Define the DHT22 sensor type
#define DHTTYPE DHT22

// Pin where the data pin of DHT22 is connected
#define DHTPIN D4

// RGB LED pins
#define RED_PIN D1
#define GREEN_PIN D2
#define BLUE_PIN D3  // Not used, but define it for future use

// Buzzer pin
#define BUZZER_PIN D5  // Connect the buzzer to this pin

// Temperature threshold (you can change this as per your requirement)
#define TEMP_THRESHOLD 30.0  // Set the temperature threshold (in Celsius)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Set RGB pins and buzzer as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Turn off all LEDs and buzzer initially
  setColor(0, 0, 0);
  noTone(BUZZER_PIN);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature as Celsius
  float temp = dht.readTemperature();

  // Read humidity
  float humidity = dht.readHumidity();

  // Check if any reading failed and exit early (to try again).
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Compare temperature with threshold and control RGB LED and buzzer
  if (temp > TEMP_THRESHOLD) {
    // Temperature exceeds threshold, glow red and turn on buzzer
    setColor(255, 0, 0);  // Red
    tone(BUZZER_PIN, 1000);  // Play a sound with 1kHz frequency
    Serial.println("Temperature is high, glowing RED and sounding buzzer.");
  } else {
    // Temperature is normal, glow green and turn off buzzer
    setColor(0, 255, 0);  // Green
    noTone(BUZZER_PIN);   // Stop the buzzer
    Serial.println("Temperature is normal, glowing GREEN and buzzer is off.");
  }
}

// Function to set the RGB LED color
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);  // Not used in this case
}
