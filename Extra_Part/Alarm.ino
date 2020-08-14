#define trigPin D2
#define echoPin D3
#define buzzer D5
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
// Define variables:
long duration;
int distance;
int open=0;
const char *ssid = "Fff";
const char *password = "nikunj12";
const char *host = "instamax.pythonanywhere.com";
HTTPClient http;
String postData;
 
void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);        
 
  WiFi.begin(ssid, password);    
  Serial.println("");
 
  Serial.print("Connecting");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 

}
void loop() {

  unsigned char i;
  int starttime, endtime;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  //Serial.println(distance);
 
  if(distance<=10)
  {
    if(open==1)
    {
      Serial.println("threat");
      starttime = millis();
      endtime = starttime;
      while((endtime-starttime)<=5000)
        {
        for(i=0;i<80;i++){
        digitalWrite(buzzer,HIGH);
        delay(1);
        digitalWrite(buzzer,LOW);
        delay(1);
        }
        endtime = millis();
       
        }
    }
    else
    {
    Serial.println("pass");
    }
  }

  http.begin("http://instamax.pythonanywhere.com/data");              
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    
 
  int httpCode = http.GET();
  String ss=http.getString();
  if(ss.indexOf("open")>=0)
  {
    open=1;
  }
  else if (ss.indexOf("close")>=0){
    open=0;}
 
 
  http.end();
 

 
  delay(500);
 
}
