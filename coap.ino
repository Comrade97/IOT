#include <coap-simple.h>
#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


#define red_led 14
#define yellow_led 12
#define green_led 13
#define DHT11_PIN 5

int temp;

SimpleDHT11 dht11(DHT11_PIN);

const char* ssid     = "Dhruv";
const char* password = "Dhruv@123";

WiFiServer server(80);

WiFiUDP udp;
Coap coap(udp);


void callback_light(CoapPacket &packet, IPAddress ip, int port) {
 
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  String message(p);
  
  if (message.equals("OFF")){
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW); 
    coap.sendResponse(ip, port, packet.messageid, "OFF");
  }
  else if(message.equals("ON")){

    const char* str;
    
    if (temp >= 45){
      digitalWrite(red_led, HIGH) ; 
      str = "R";
    }
    else if (temp >= 30){
      digitalWrite(yellow_led, HIGH) ;
      str = "Y";
    }
    else{
      digitalWrite(green_led, HIGH) ;
      str = "G";
    }
    coap.sendResponse(ip, port, packet.messageid, str);
  }
}


void callback_response(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Coap Response got]");
  
  char p[packet.payloadlen + 1];

  
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  Serial.println(p);
}


void setup(){
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  pinMode(red_led,OUTPUT);
  pinMode(yellow_led,OUTPUT);
  pinMode(green_led,OUTPUT);

  coap.server(callback_light, "temperature/light");
  Serial.println("Setup Callback Light");
  
  coap.response(callback_response);
  Serial.println("Setup Response Callback");

  coap.start();
}

void loop(){
  
  byte temperature = 0;
  byte humidity = 0;
  
  int err = SimpleDHTErrSuccess;
  dht11.read(&temperature, &humidity, NULL);
  
  temp = (int)temperature;
  Serial.print("Temperature = ");
  Serial.println((int)temperature);
  
  delay(10000);
  coap.loop();
}
