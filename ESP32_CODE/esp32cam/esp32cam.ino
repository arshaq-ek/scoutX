#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi Credentials
const char* ssid = "EDUVAMMAL-2.4G";
const char* password = "EDUVAMMAL775";

// Web server on port 80
AsyncWebServer server(80);

// Define Serial2 pins (ESP32 TX → Arduino RX, ESP32 RX → Arduino TX)
#define TX_PIN 2   
#define RX_PIN 12  

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  // Connect to Wi-Fi with timeout
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed. Restarting...");
    ESP.restart();
  }

  // Handle movement commands
  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("dir")) {
      String command = request->getParam("dir")->value();
      Serial.println("Received command: " + command);
      Serial2.println(command); // Forward to Arduino Mega
      request->send(200, "text/plain", "Command received: " + command);
    } else {
      request->send(400, "text/plain", "No command provided");
    }
  });

  server.begin();
}

void loop() {
  // ESP32 continuously listens for HTTP requests
}
