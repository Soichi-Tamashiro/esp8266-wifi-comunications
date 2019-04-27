/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
}

void loop() {
  client.connect(server, 80);
//  digitalWrite(ledPin, LOW);
//  client.flush();
//  Serial.println("********************************");
//  Serial.print("Byte sent to the AP: ");
//  Serial.println(client.println("x\r"));
//  String x= client.readStringUntil('\r');
//  client.flush();
//  Serial.println("********************************");
//  Serial.print("Byte sent to the AP: ");
//  Serial.println(client.println("yy\r"));
//  String y= client.readStringUntil('\r');
//  client.flush();
//  Serial.println("********************************");
//  Serial.print("Byte sent to the AP: ");
//  Serial.println(client.println("z\r"));
//  String z= client.readStringUntil('\r');
//  client.flush();
//  Serial.println("********************************");
//  Serial.println("Angle X : " + x);
//  Serial.println("Angle Y : " + y);
//  Serial.println("Angle Z : " + z);
//  digitalWrite(ledPin, HIGH);
//  client.stop();
  delay(200);
}

