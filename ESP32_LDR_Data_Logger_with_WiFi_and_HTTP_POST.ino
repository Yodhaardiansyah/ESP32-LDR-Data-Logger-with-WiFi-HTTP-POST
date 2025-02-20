/*
 * ESP32 LDR Data Logger with WiFi and HTTP POST
 * 
 * This program reads LDR (Light Dependent Resistor) values using ESP32 and sends data to a web server via WiFi.
 * 
 * Created by: Yodha Ardiansyah
 * Instagram: @yodhaar_
 */

#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials (Replace with your own)
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// Server URL (Replace with your own)
const char* serverBaseUrl = "http://www.yourwebsite.com/api/post_data.php";

// LDR Pin
const int ldrPin = 39; // Analog pin for LDR (ADC1_CH3)

// ID parameter
String id_ver = "0101";

void setup() {
  Serial.begin(115200);
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void loop() {
  // Read LDR value
  int ldrValue = analogRead(ldrPin);
  Serial.println("LDR Value: " + String(ldrValue));

  // Send data via HTTP POST if WiFi is connected
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Full server URL with query parameters
    String serverUrl = String(serverBaseUrl) + "?id_ver=" + id_ver;

    // Initialize HTTP POST
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Data to be sent in JSON format
    String postData = "{\"data\":\"" + String(ldrValue) + "\"}";

    // Debug HTTP request
    Serial.println("HTTP POST URL: " + serverUrl);
    Serial.println("HTTP POST Data: " + postData);

    // Send data to server
    int httpResponseCode = http.POST(postData);

    // Print server response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error: " + String(httpResponseCode));
    }

    // Close connection
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(5000); // Wait 5 seconds before sending again
}
  