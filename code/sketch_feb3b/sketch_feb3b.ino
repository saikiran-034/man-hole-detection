#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#include <SoftwareSerial.h>
#include <dht11.h>
#define RX 9
#define TX 10
#define dht_apin 11 // Analog Pin sensor is connected to
dht11 dhtObject;
int sensorPin = A0; 
#define trigger A1
#define echo A2
int sensorValue = 0; 
int led = 12;
String AP = "elegant";       // AP NAME
String PASS = "smartwork"; // AP PASSWORD
String API = "KA5N7CVOXCUBVBWW";   // API KEY FROM THINGSPEAK
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
float time=0,distance=0;
  
SoftwareSerial esp8266(RX,TX); 
  
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("IOT BASED MANHOLE");
  lcd.setCursor(0, 1);  lcd.print("  MONITORING");
  delay(1000);
  pinMode(led, OUTPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() 
{
  
 String getData = "GET /update?api_key="+ API +"&field1="+getTemperatureValue()+"&field2="+getHumidityValue()+"&field3="+getldrvalur()+"&field4="+getlevel();
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");

}


String getTemperatureValue(){
   
   dhtObject.read(dht_apin);
   Serial.print("Temperature(C)= ");
   lcd.setCursor(0, 1); 
   lcd.print("Temperature=");
   float  temp = dhtObject.temperature;
   Serial.println(temp);
   lcd.print(temp);
   delay(100);
   return String(temp); 
  
}


String getHumidityValue(){

   dhtObject.read(dht_apin);
   
   Serial.print(" Humidity in %=");
   lcd.clear();
   lcd.print("Humidity%=");
   float humidity = dhtObject.humidity;
   Serial.println(humidity);
   lcd.print(humidity);
   delay(100);
   return String(humidity); 
  }


String getldrvalur()
{
lcd.clear();

sensorValue = analogRead(sensorPin);

Serial.println(sensorValue);

if (sensorValue < 100)

{
digitalWrite(led,HIGH);
delay(1000);

}
else
{
  lcd.clear();
digitalWrite(led,LOW);
delay(1000);

}
return String(sensorValue);
}


String getlevel()
{
 lcd.clear();
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
 lcd.clear();
 /*Serial.print("Distance:");
 Serial.print(distance);
 Serial.print("cm..");*/
 lcd.print("Distance:");
 lcd.print(distance);
 lcd.print("cm");
 lcd.setCursor(0,1);
 lcd.print("Distance:");
 lcd.print(distance/100);
 lcd.print("m");
 delay(500);
 if(distance<30)
 {

  Serial.print("Obstracle near:");
  Serial.print(distance);
  Serial.print("centimeters");
  delay(1000);
}
return String(distance);
 
 }


void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
