#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>
#include<DHT.h>
#define DHTTYPE DHT11
#define DHTPIN D1
DHT dht(DHTPIN,DHTTYPE);
WiFiClient client;

const char* ssid = "Pris";
const char* password ="prisca123";
unsigned long channelnum =3044220;
const char* apikey ="O87QGHX379UE76PX";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("thing speak");
WiFi.begin(ssid,password);
Serial.println("connecting to wifi");
while(WiFi.status()!=WL_CONNECTED){
Serial.print(". ");
delay(500);


}
dht.begin();
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:
float temp = dht.readTemperature();
float hum = dht.readHumidity();
/*
int randomnum = random(1,100);
Serial.println("sending data:");
Serial.println(randomnum);*/
Serial.println("sending data. temperature:");
Serial.println(temp);
Serial.println("humidity:");
Serial.println(hum);
ThingSpeak.setField(2,temp);
ThingSpeak.setField(3,hum);
int statuscode = ThingSpeak.writeFields(channelnum,apikey);

if (statuscode=200){
  Serial.println(" data sent ");
}
else{Serial.println("  error, http code:");
Serial.println(statuscode);}

delay(20000);
}
