#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
 
// Define a data structure
typedef struct struct_message {
  // char a[32];
  int b;
  int c;
  // bool d;
} struct_message;
 
// Create a structured object
struct_message myData;

#define led 8
#define dim 0
#define relay2 1

bool buzzerState = LOW;
bool saklar = LOW;

// anti bounce variables
bool saklarbounce = HIGH;
bool dimbounce = HIGH;


unsigned long previousMillis = 0; // Store the last time LED was updated 


// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.print("Data received: ");
  // Serial.println(len);
  // Serial.print("Character Value: ");
  // Serial.println(myData.a);
  // Serial.print("Integer Value: ");
  // Serial.println(myData.b);

  // saklar dim
  buzzerState = myData.b;

  // saklar
  saklar = myData.c;
  // Serial.println(myData.c);

  // Serial.print("Boolean Value: ");
  // Serial.println(myData.d);
  // bool status = myData.d;
  // Serial.println();
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  pinMode(dim, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(dim, LOW);
  digitalWrite(relay2, LOW);
  
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

bool saklarState = false;

void loop() {
  if (buzzerState) {
    digitalWrite(dim, HIGH); 
  } else {
    digitalWrite(dim, LOW); 
  }

  if (buzzerState == HIGH && dimbounce == LOW)
  {
    previousMillis = millis();
  }
  
  dimbounce = buzzerState;

  if (saklar == HIGH && saklarbounce == LOW) {
    saklarState = !saklarState;
    digitalWrite(relay2, saklarState ? HIGH : LOW);
  }
  saklarbounce = saklar;


    if (millis() - previousMillis >= 5000 && buzzerState == HIGH) 
  {
    buzzerState = LOW;
  } 
}