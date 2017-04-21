#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

const char* ssid = "elsys";
const char* password = "";

WiFiUDP Udp;
unsigned int localUdpPort = 20250;  // local port to listen on
char incomingPacket[511];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back
char command[511];
char *separator;
char *address;
char s[511];

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
  command[0] = '\0';

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  int l, i;
  int packetSize = Udp.parsePacket();
  byte ip[4];
  char* convert;
  if (Serial.available() > 0)
  {
    Serial.readBytesUntil('\0', replyPacket, 1038);
    if (!(strcmp(replyPacket, "?")))
    {
      l = strlen(command);
      Serial.println(l);
      if (l)
      {
        Serial.println(command);
        command[0] = '\0';
      }
    }
    else
    {
      strcpy(s, replyPacket);
      char * cr_parse;
      cr_parse = strtok(replyPacket, "#;");
      Serial.println("THIS IS THE START");
      while (cr_parse != NULL) {
        Serial.println(cr_parse);
        if(cr_parse[0] == '1') {
          address = cr_parse; 
          Serial.println(cr_parse);
          break;
        }
        cr_parse = strtok (NULL, " ,.-");
        Serial.println("END PARSE");
        Serial.println(cr_parse);
      }
      cr_parse = s+strlen(cr_parse)+1;
      cr_parse=strcat("###", cr_parse);
      strcpy(replyPacket, cr_parse);
      parseBytes(address, '.', ip, 4, 10);
      Serial.println(replyPacket);
      Udp.beginPacket(ip, localUdpPort);
      Udp.write(replyPacket);
      Udp.endPacket();
      command[0] = '\0';
    }
    //address[0] = '\0';
  }
  // receive incoming UDP packets
  //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
  int len = Udp.read(incomingPacket, 511);
  if (len > 0)
  {
    Serial.println("DEBAMAMIKAMU");
    incomingPacket[len] = '\0';
    strcpy(s, Udp.remoteIP().toString().c_str());
    l=strlen(s);
    convert = strcat("###", s);
    strcpy(s, convert);
    s[l+3]='\0';
    Serial.println("S:");
    Serial.println(s);
    strcpy(command, s);
    Serial.println("1st Commmand state:");
    Serial.println(command);
    convert = strcat(command, ";");
    strcpy(command, convert);
    Serial.println("2nd Commmand state:");
    Serial.println(command);
    convert = strcat(command, incomingPacket + 3);
    strcpy(command, convert);
    Serial.println("Final state:");
    Serial.println(command);

  }
  //Serial.printf("UDP packet contents: %s\n", incomingPacket);
  // send back a reply, to the IP address and port we got the packet from

  /*Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacekt);
    Udp.endPacket();*/
  //address[0] = '\0';
}

void parseBytes(const char* str, char sep, byte* bytes, int maxBytes, int base) {
  for (int i = 0; i < maxBytes; i++) {
    bytes[i] = strtoul(str, NULL, base);  // Convert byte
    str = strchr(str, sep);               // Find next separator
    if (str == NULL || *str == '\0') {
      break;                            // No more separators, exit
    }
    str++;                                // Point to next character after separator
  }
}
