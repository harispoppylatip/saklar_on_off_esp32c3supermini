#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
 
// Define a data structure
typedef struct struct_message {
  // char a[32];
  int b;
  // float c;
  // bool d;
} struct_message;
 
// Create a structured object
struct_message myData;

#define led 8
 
unsigned long previousMillis = 0; // Store the last time LED was updated 


void toggleLED(bool o) {
  digitalWrite(led, o ? HIGH : LOW);

  }
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  // Serial.print("Character Value: ");
  // Serial.println(myData.a);
  Serial.print("Integer Value: ");
  Serial.println(myData.b);
  // Serial.print("Float Value: ");
  // Serial.println(myData.c);
  // Serial.print("Boolean Value: ");
  // Serial.println(myData.d);
  // bool status = myData.d;
  // if (myData.d == true) {
  //   previousMillis = millis();
  // }
  Serial.println();
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // if (millis() - previousMillis <= 10000)
  // {
  //   toggleLED(false);
  // } 
  // else 
  // {
  //   toggleLED(true);
  // }
  
 
}