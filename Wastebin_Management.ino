
#include <SPI.h>
#include <Ethernet.h>
#include "ThingSpeak.h"
const int trigPin = A1;
const int echoPin = A0;
const int buzzer1 = 9;
const int buzzer2 = 10;
int led1 = 7; 
int led2 = 6;
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

unsigned long myChannelNumber = 966871;
const char * myWriteAPIKey = "ZZXUE6WU3CT8Q0C8" ;
long duration;
int distance;
int percentage;

IPAddress ip(192, 168, 0, 177);
void setup() 
{
//    Ethernet.init(10);  
    Serial.begin(9600); // Starts the serial communication

      if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
     Ethernet.begin(mac, ip);
       pinMode(led1, OUTPUT);
       pinMode(led2, OUTPUT);
       pinMode(buzzer1, OUTPUT);
       pinMode(buzzer2, OUTPUT); // Set buzzer - pin 9 as an output
  }
  // give the Ethernet shield a second to initialize:
  delay(250);
  Serial.println("connecting...");
    ThingSpeak.begin(client);  
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  delay(250);//Delay to let system boot
  delay(100);//Wait before accessing Sensor
  pinMode(2, INPUT);


}

void loop()
{
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
    delay(1000);//Wait 5 seconds before accessing sensor again.
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("level of garbage : ");
    Serial.println(distance);
    if(distance<= 10){
        tone(buzzer1, 1000);
        tone(buzzer2, 1000);// Send 1KHz sound signal...
        digitalWrite(led2, HIGH);
        digitalWrite(led1, LOW);
        delay(1000);        // ...for 1 sec
        noTone(buzzer1);
        noTone(buzzer2);    // Stop sound...
        delay(1000);        // ...for 1sec
      }
    percentage= 100-(distance-1);
      //else
    delay(4000);
  ThingSpeak.setField(1, distance);
ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
 delay(1000);
}
