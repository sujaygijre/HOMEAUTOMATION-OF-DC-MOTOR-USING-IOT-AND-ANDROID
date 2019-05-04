#include<SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(2,3);
void setup() {
  int mPin4=4;
int mPin5=5;
int poT;
  Serial.begin(9600);
  esp8266.begin(9600);
  Serial.println("ready!");
  // put your setup code here, to run once:
  pinMode(mPin4,OUTPUT);
digitalWrite(mPin4,LOW);
pinMode(mPin5,OUTPUT);
analogWrite(mPin5,127);
 pinMode(11,OUTPUT);
 digitalWrite(11,LOW);

 pinMode(12,OUTPUT);
 digitalWrite(12,LOW);

 pinMode(13,OUTPUT);
 digitalWrite(13,HIGH);

 sendData("AT+RST\r\n",2000,DEBUG);
 sendData("AT+CWMODE_CUR=3\r\n",1000,DEBUG);
sendData("AT+CWJAP=\"jio1\",\"sujaygijre123\"\r\n",5000,DEBUG);
delay(3000);
sendData("AT+CIFSR\r\n",3000,DEBUG);
delay(1000);
sendData("AT+CIPMUX=1\r\n",2000,DEBUG);
sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
}

void loop() {
  // put your main code here, to run repeatedly:
if(esp8266.available())
{
  if(esp8266.find("+IPD,"))
  {
    delay(1000);
    int connectionid=esp8266.read()-48;
    esp8266.find("pin=");
    int pinNumber=(esp8266.read()-48)*10;
    pinNumber+=(esp8266.read()-48);
    
    
    
    digitalWrite(pinNumber,!digitalRead(pinNumber));
int mPin5=5;
if(pinNumber==13)
{
  analogWrite(mPin5,75);
  }
  if(pinNumber==12)
  {
     analogWrite(mPin5,127);
    }
    if(pinNumber==11)
    {
        analogWrite(mPin5,255);
      }

      
    String closeCommand="AT+CIPCLOSE=";
    closeCommand+=connectionid;
    closeCommand+="\r\n";


    sendData(closeCommand,1000,DEBUG);
    }
   


  }
}

String sendData(String command,const int timeout,boolean debug)
{
  String response="";
  esp8266.print(command);
  long int time=millis();
  while((time+timeout)>millis())
  {
    while(esp8266.available())
    {
      char c = esp8266.read();
      response+=c;
      }
    }
    if(debug)
    {
      Serial.print(response);
      }
      return response;
  }
