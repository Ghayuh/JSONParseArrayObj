#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "yourSSID";
const char* password = "yourPassword";
const char* domain_get = "http://5-dot-dev-inno-cloud.appspot.com/blukey/ble";
String payload;
const char* mac;
const char* uuid;
uint8_t counter;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
}

void loop() {
  getData();
  parseJson();
}

void getData(){
  if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;

      http.begin(domain_get);
      int httpCode = http.GET();

      if(httpCode > 0){
         payload = http.getString();
        }
      http.end();
    }
}

void parseJson(){
  StaticJsonBuffer<1200> jsonBuffer;
  JsonArray& root = jsonBuffer.parseArray(payload);

  for(counter=0;counter < 3;counter++){
      JsonObject& a = root[counter];

      mac = a["mac"];
      uuid = a["uuid"];
    
      Serial.println(mac);
      Serial.println(uuid);
    }

  if(!root.success())
  {
    Serial.println("parseArray() failed");
    return;
  }
}
