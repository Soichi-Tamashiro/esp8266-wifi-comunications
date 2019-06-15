/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */
//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;
//----------------------------------------------------------------
void setup() {
//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
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
//----------------------------------------------------------------
// Configuración de WiFi
//----------------------------------------------------------------
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
//----------------------------------------------------------------
// Recepción de datos por wifi
//----------------------------------------------------------------  client.flush();
  String request = client.readStringUntil('\r');
  Serial.println(request);

  client.stop();
  delay(200);
}

