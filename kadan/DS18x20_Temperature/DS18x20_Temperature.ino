#include <OneWire.h>
#include <DallasTemperature.h>
#define FASTLED_INTERNAL
//
#include <M5Atom.h>
#include <WiFi.h>
#include <HTTPClient.h>
//
const char* ssid = "superdoro";
const char* password = "tel371896";
//humi
#include "DHT.h"
#define DHTPIN G26     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS G25
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

float check(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  //Serial.print("Requesting temperatures...");
  sensors.begin();
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  //Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.print(sensors.getTempCByIndex(0));
  float val =  sensors.getTempCByIndex(0);
  Serial.print(val);
  return (int) (val * 100);
}


void post(String str) {
  HTTPClient http;
  http.begin("https://script.google.com/macros/s/AKfycbzxXlQRFPsN0_t-DisyGta77vgK7saU7ASF6-Uz2NYx43fW7sMDc0uKSYwwiHPvRRJdRA/exec?a=" +str );
  //http.addHeader("Content-Type", "application/json");
  http.GET();
  Serial.println(str);

  http.end();
}

void setup() {
  int val = check() ;// これを呼ばないとあとで読みだせなくなる
  dht.begin();
  //M5.begin();
  M5.begin(true, false, true);
  // Powerの初期化
 // M5.Power.begin();  
  Serial.begin(9600);
  Serial.print("WiFi connecting.");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
}

void loop() {

post(String(check()));
 esp_deep_sleep(180*1000000);
}
