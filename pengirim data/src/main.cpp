#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define btn 0
 
// Variables for test data
int int_value;
float float_value;
bool bool_value = true;
 
// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x18, 0x8B, 0x0E, 0x2C, 0x24, 0xC8};
 
// Define a data structure
typedef struct struct_message {
  // char a[32];
  int b;
  // float c;
  // bool d;
} struct_message;
 
// Create a structured object
struct_message myData;
 
// Peer info
esp_now_peer_info_t peerInfo;
 
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Serial.print("\r\nLast Packet Send Status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(btn, INPUT_PULLUP);
 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
 
  // Create test data
 
  // Generate a random integer
  int_value = digitalRead(btn);
 
  // Use integer to make a new float
  // float_value = 1.3 * int_value;
 
  // Invert the boolean value
  // bool_value = digitalRead(btn);
  
  // Format structured data
  // strcpy(myData.a, "Welcome to the Workshop!");
  myData.b = !int_value;
  // myData.c = float_value;
  // myData.d = a;

  // Serial.print("Sending data: ");
  // Serial.print(myData.d);
  // Serial.println(", ");
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  // if (result == ESP_OK) {
  //   Serial.println("Sending confirmed");
  // }
  // else {
  //   Serial.println("Sending error");
  // }
  delay(50);
}