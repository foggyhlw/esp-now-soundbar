
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0x48, 0x3f, 0xda, 0x07, 0x27, 0x62}; 

#define BUTTON1 12
#define BUTTON2 14

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char mac[16];
  int buttonNumber;
  float batteryVoltage;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  // Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    // Serial.println("Delivery success");
  }
  else{
    // Serial.println("Delivery fail");
  }
}
 
void setup() {
  // battery.begin(3300, 1.47, &sigmoidal);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  // Init Serial Monitor
  // Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    // Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  strcpy(myData.mac, WiFi.macAddress().c_str());
    // strcpy(myData.mac,"mac1");

    if(digitalRead(BUTTON1) == LOW){
      myData.buttonNumber = BUTTON1;
    }
    if(digitalRead(BUTTON2) == LOW){
      myData.buttonNumber = BUTTON2;
    }
   myData.batteryVoltage = analogRead(A0)*5.7/1023;
// myData.batteryVoltage = battery.level();

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
}
 
void loop() {

}