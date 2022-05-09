#include "EspMQTTClient.h"
#include "SimpleDHT.h"
#define led 4
#define dht_11 5
SimpleDHT11 dht11(dht_11);
EspMQTTClient client(
 "Dhruv",
 "Dhruv@l23",
 "18.195.132.243", // MQTT Broker server ip
 "", // Can be omitted if not needed
 "", // Can be omitted if not needed
 "Dhruv" // Client name that uniquely identify your device
);
void setup() {
 Serial.begin(9600);
 pinMode(led,OUTPUT);
}
void onConnectionEstablished() {
 client.publish("NirmaUniversity/ITNU/N505/19BCE121", "Connection Established");
}
void loop() {
 client.loop();
 byte temperature = 0;
 byte humidity = 0;
 int err = SimpleDHTErrSuccess;
 if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
 delay(2000);
 return;
 }

 int temp = (int)temperature;
 int hum = (int)humidity;
 Serial.print("Temperature = ");
 Serial.println((int)temperature);
 Serial.print("Humidity = ");
 Serial.println((int)humidity);
 client.publish("NirmaUniversity/ITNU/N505/Dhruv", "Temperature at ITNU N505 :
"+(String)temp+" And Humidity at ITNU N505 : "+(String)hum);
 client.subscribe("NirmaUniversity/ITNU/N505/Dhruv/led", [] (const String &payload) {
 Serial.println(payload);
 if (payload.compareTo("ON")==0){
 digitalWrite(led,HIGH);
 }
 else{
 digitalWrite(led,LOW);
 }
 });

 delay(1000);
}
