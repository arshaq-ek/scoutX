#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi credentials
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// Create an asynchronous web server on port 80
AsyncWebServer server(80);

// Define Serial2 pins for communication with Arduino UNO
#define TX_PIN 4   // ESP32 TX → Arduino UNO RX
#define RX_PIN 12  // ESP32 RX → Arduino UNO TX

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // (Optional) Set up a placeholder endpoint for video streaming
  server.on("/stream", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Camera Stream Enabled!");
  });

  // Movement command API endpoint
  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("dir")) {
      String command = request->getParam("dir")->value();
      Serial2.println(command); // Forward command to Arduino UNO
      request->send(200, "text/plain", "Command Received: " + command);
    } else {
      request->send(400, "text/plain", "No command provided");
    }
  });

  server.begin();
}

void loop() {
  // ESP32 continuously listens for HTTP requests
}
