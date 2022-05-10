int timer=1000;
int counter=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  Serial.println("Binary Counter");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D4,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D0,LOW);
  delay(timer);

  counter++;

  if((counter%2)>0)
    digitalWrite(D0,HIGH);
  else
    digitalWrite(D0,LOW);

  if((counter%4)>1)
    digitalWrite(D1,HIGH);
  else
    digitalWrite(D1,LOW);

  if((counter%8)>3)
    digitalWrite(D2,HIGH);
  else
    digitalWrite(D2,LOW);

  if((counter%16)>7)
    digitalWrite(D3,HIGH);
  else
    digitalWrite(D3,LOW);

  if((counter%32)>15)
    digitalWrite(D4,HIGH);
  else
    digitalWrite(D4,LOW);

  delay(timer);
}
