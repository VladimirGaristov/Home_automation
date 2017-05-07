#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

const char* ssid = "elsys";
const char* password = "";

WiFiUDP Udp;
char s_php[511], s_wifi[511];
int i;
char ip[16];

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void php_to_wifi(char * s_php, char * s_wifi)
{
  for()
}

