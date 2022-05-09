const int trigPin=12; // D6 
const int echoPin=14; // D5

#define SOUND_VELOCITY 0.0343
#define CM_TO_INCH 0.393701

long duration;
float distanceCM;
float distanceINCH;

const int outputD1=D1;
//const int outputD2=D2;

void setup(){
    Serial.begin(115200);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);

    pinMode(outputD1,OUTPUT);
    //pinMode(outputD2,OUTPUT);

    digitalWrite(trigPin,LOW);
    digitalWrite(echoPin,LOW);
  }

void loop(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    duration=pulseIn(echoPin,HIGH);

    distanceCM=duration*SOUND_VELOCITY/2;
    distanceINCH=distanceCM*CM_TO_INCH;

    if(distanceCM<=8){
        int i=1;
        while(i<5){
          digitalWrite(outputD1,HIGH);
          //digitalWrite(outputD2,HIGH);
          delay(3);
          digitalWrite(outputD1,LOW);
          //digitalWrite(outputD2,LOW);
          i=i+1;
        }
      }
     else if(distanceCM<=20&&distanceCM>8){
          int i=1;
          while(i<5){
            digitalWrite(outputD1,HIGH);
            delay(30);
            digitalWrite(outputD1,LOW);
            i=i+1;
          }
        }
      else if(distanceCM<=50&&distanceCM>20){
          int i=1;
          while(i<5){
            digitalWrite(outputD1,HIGH);
            delay(60);
            digitalWrite(outputD1,LOW);
            i=i+1;
          }
        }

    Serial.print("distance in centimeters : ");
    Serial.println(distanceCM);
    Serial.print("distance in inches : ");
    Serial.println(distanceINCH);

    delay(400);
  }
