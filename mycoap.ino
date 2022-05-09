#include <coap-simple.h>
#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define simple_led 12
#define DHT11_PIN 5

int temp;

SimpleDHT11 dht11(DHT11_PIN);

const char* ssid     = "Dhruv";
const char* password = "Dhruv@123";

WiFiServer server(80);

WiFiUDP udp;
Coap coap(udp);


void callback_light(CoapPacket &packet, IPAddress ip, int port) {

  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  String message(p);

  if(message.equals("OFF")) {
    digitalWrite(simple_led,LOW);
    coap.sendResponse(ip, port, packet.messageid, "OFF");
  }
  else if(message.equals("ON")) {

    //const char* str[] = {"Temperature"};
    digitalWrite(simple_led,HIGH);
    coap.sendResponse(ip, port, packet.messageid, "ON");
  }
  //const char* str = (const char*)temp;
  
  if (temp >= 45){
      coap.sendResponse(ip, port, packet.messageid, "Heat");
    }
    else if (temp >= 30){
      coap.sendResponse(ip, port, packet.messageid, "Medium");
    }
    else{
      coap.sendResponse(ip, port, packet.messageid, "Cold");
    }
}


void callback_response(CoapPacket &packet, IPAddress ip, int port) {

  Serial.println("[Coap Response got]");
  
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  Serial.println(p);
}

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting with ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // If wifi is not connected then just printing ...
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // As soon as Wifi is connected print IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  pinMode(simple_led,OUTPUT);
  
  coap.server(callback_light, "led/temperature");
  Serial.println("Setup Callback Light");
  
  coap.response(callback_response);
  Serial.println("Setup Response Callback");

  coap.start();
}


void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  dht11.read(&temperature, &humidity, NULL);
  
  temp = (int)temperature;
  Serial.print("Temperature = ");
  Serial.println((int)temperature);
  
  delay(1000);
  coap.loop();
}
