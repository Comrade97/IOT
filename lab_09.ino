#include <DHT.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h" 

#define DHTPIN 2          //DHT11 is connected to GPIO Pin 2

char ssid[] = "itsmebro";   // your network SSID (name)
char pass[] = "Dhruv@12345";   // your network password

unsigned long myChannelNumber = 1715761;
const char * myWriteAPIKey = "25XRUR0RPC9FCFG3";
 
String humi;
String temp;
 
DHT dht(DHTPIN, DHT11);
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
       WiFi.mode(WIFI_STA);
       
      ThingSpeak.begin(client); 

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");   
    }
    Serial.println("\nConnected.");
  }      
}
 
void loop() 
{
  
      humi = dht.readHumidity();
      temp = dht.readTemperature();

      //Serial.println("Temperature: "+String(temp));
      //Serial.println("Humidity: "+String(humi));
 
      int x = ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);
      int y = ThingSpeak.writeField(myChannelNumber, 2, humi, myWriteAPIKey);
      if(x == 200 && y==200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
        Serial.println("Problem updating channel. HTTP error code " + String(y));
      }
  
    delay(5000);
}
