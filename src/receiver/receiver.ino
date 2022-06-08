/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/ 
#define INPUT_BUTTON_PIN 14  // local control button
#define BUZZER_PIN 12   // buzzer pin
#define BUTTON_NUMBER_1 12  // 12 is the number sent by esp-now sender, representing BUTTON_NUMBER_1
#define BUTTON_NUMBER_2 14 // 14 is the number sent by esp-now sender, representing BUTTON_NUMBER_1
#define RELAY_POWER 4
#define RELAY_LED 2

#include <ESP8266WiFi.h>
#include <espnow.h>
#include "fastled_effects.h"
#include "Button2.h"
// #include "beep.h"

int effect_mode = 0;  //led effect 
int MODE_NUM = 6;

Button2 button = Button2(INPUT_BUTTON_PIN);
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char mac[16];
  int buttonNumber;
  float batteryVoltage;
} struct_message;

// Create a struct_message called myData
struct_message myData;
int battery = 100;
bool power_state = false;
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("MAC: ");
  Serial.println(myData.mac);
  Serial.print("Button Nmumber: ");
  Serial.println(myData.buttonNumber);
  Serial.print("Battery Voltage: ");
  Serial.println(myData.batteryVoltage);
  battery = myData.batteryVoltage;
  Serial.println();

  if (myData.buttonNumber == BUTTON_NUMBER_1){
    change_power_state();
  }
  if (myData.buttonNumber == BUTTON_NUMBER_2){
    cycle_choose_led_effect();
  }
}
 
void setup() {
  pinMode(RELAY_POWER, OUTPUT);
  pinMode(RELAY_LED, OUTPUT);
  // buzzer_setup(); 
  button.setClickHandler(single_click_handler);
  button.setLongClickHandler(longClick_handler);
  // Initialize Serial Monitor
  Serial.begin(115200);
  fastled_setup();
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("MY MAC ADDRESS IS: ");
  Serial.print(WiFi.macAddress());
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

  if (digitalRead(RELAY_LED)!= HIGH && power_state == true){
    digitalWrite(RELAY_LED, HIGH); 
  }
    switch(effect_mode){
      case 0: show_battery_level(battery);break;
      case 1: rainbow_effect_loop();break;
      case 2: palette_effect_loop();break;
      case 3: dot_beat_loop();break;
      case 4: blur_loop();break;
      case 5: black_effect_loop();break;
    }
  button.loop();
  // buzzer_loop();
}

void cycle_choose_led_effect(){
  if(effect_mode < MODE_NUM){
    effect_mode++;
  }
  if(effect_mode >= MODE_NUM){
    effect_mode = 0;
  }
  // Serial.print(screen_saver_mode);
}

void change_power_state(){
if( digitalRead(RELAY_POWER) == HIGH ){
    // buzzer_beep_off();
    // effect_mode = 0;   //start effect on next start
    black_effect_loop();
    digitalWrite(RELAY_LED, LOW);  //turn off ws2815 if soundbar is off
    power_state = false;
  }
  else{
    // buzzer_beep_on();
    digitalWrite(RELAY_LED, HIGH);  //turn on ws2815 if soundbar is on
    show_battery_level(myData.batteryVoltage);
    power_state = true;
  }
  digitalWrite(RELAY_POWER, !digitalRead(RELAY_POWER)); // toggle soundbar
}

void single_click_handler(Button2& btn){
  // buzzer_single_click();
  cycle_choose_led_effect();
}

void longClick_handler(Button2& btn){
  change_power_state();
}
