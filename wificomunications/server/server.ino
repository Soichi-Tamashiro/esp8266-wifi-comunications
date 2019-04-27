/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
 *       https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
 *       https://github.com/esp8266/Arduino/issues/504
 *  Works with: station_bare_01.ino
 */ 

//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;
//----------------------------------------------------------------
// Configuración de MPU-6050
//----------------------------------------------------------------
#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
String a;

void setup() {
//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Wemos_AP", "Wemos_comm");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
//----------------------------------------------------------------
// Configuración de MPU-6050
//----------------------------------------------------------------
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
//  Serial.begin(9600);

}

void loop() {
//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
  WiFiClient client = server.available();
  if (!client) {return;}
  digitalWrite(ledPin, LOW);
//  String request = client.readStringUntil('\r');
//  Serial.println("********************************");
//  Serial.println("From the station: " + request);
//  client.flush();
//  Serial.print("Byte sent to the station: ");
//  Serial.println(client.println(request + "ca" + "\r"));
  digitalWrite(ledPin, HIGH);
//----------------------------------------------------------------
// Configuración de MPU-6050
//----------------------------------------------------------------
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

       x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

     Serial.print("ypr\t");
     Serial.print(x);
     Serial.print("\t");
     Serial.print(y);
     Serial.print("\t");
     Serial.println(z);
//----------------------------------------------------------------
// Envio de datos por wifi
//----------------------------------------------------------------
//  String request = client.readStringUntil('\r');
//  client.flush();
//  Serial.println("********************************");
//  Serial.println("From the station: " + request);
//  if (request=="angle"){
//    Serial.print("Byte sent to the station: ");
//    Serial.print(client.print(String(x, 2) + "\r"));
//    client.flush();
//  }
//
//  client.stop();
  delay(400);
}
