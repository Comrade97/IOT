void setup() {
 //pinMode(led_pin, OUTPUT);
 Serial.begin(9600);
}

void loop() {

 if (Serial.available()) 
    {
      char data_received; 
      data_received = Serial.read();  
      if (data_received == 'O')
      {
       //digitalWrite(led_pin, HIGH);
       Serial.write("Message received: ");
       Serial.write("LED is now ON!\n");        
      }
      else if (data_received == 'X')
      {
       //digitalWrite(led_pin, LOW);
       Serial.write("Message Received: ");
       Serial.write("LED is now OFF!\n");
      }
      else 
      {
       Serial.write("Specify correct option\n");
      }
    }
}
