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
char address[511];
char s[511];
//int j=0;
int i, l;
char lenght[4];
char fuckdis[5]="###";
char zadaraboti[40]="1234567891234567891234567asdfgtrdsh8912";

void setup()
{
	//fuckdis[4]='\0';
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
	/*if (Serial.available() > 0)
	{
	i=Serial.readBytesUntil('\0', replyPacket, 1038);
	replyPacket[i]='\0';
	if (!(strcmp(replyPacket, "?")))
		{
		Serial.print("0026");
		Serial.print("###192.168.95.");
		Serial.print(j);
		Serial.print(";I;duy");
		Serial.print(j);
		Serial.print(";###");
		j++;
		}
	}*/
	int packetSize = Udp.parsePacket();
	byte ip[4];
	char* convert;
	if (Serial.available() > 0)
	{
		i=Serial.readBytesUntil('\0', replyPacket, 510);
		replyPacket[i]='\0';
		if (!(strcmp(replyPacket, "?")))
		{
			l = strlen(command);
			//Serial.println(l);
			if (l)
			{
			for(i=0;i<4;i++)
			{
				lenght[3-i]=l%10+48;
				l/=10;
			}
			Serial.print(lenght);
			Serial.print(command);
			command[0] = '\0';
			}
		}
		else
		{
			//Serial.println(replyPacket);
			l=strlen(replyPacket);
			s[0]='\0';
			strcpy(s, replyPacket);
			s[l]='\0';
			char * cr_parse;
			cr_parse = strtok(replyPacket, "#;");
			if (cr_parse != NULL)
			{
			strcpy(address, cr_parse);
			}
			cr_parse = s+strlen(cr_parse)+4;
			l=strlen(cr_parse);
			convert=NULL;
			convert=strcat(fuckdis, cr_parse);
			//Serial.println(address);
			parseBytes(address, '.', ip, 4, 10);
			strcpy(s, zadaraboti);
			strcpy(s, convert);
			s[l+3]='\0';
			//Serial.println(s);
			//Serial.println(strlen(s));
			//Serial.println(ip);
			Udp.beginPacket(ip, 20300);
			Udp.write(s, strlen(s));
			Udp.endPacket();
			//Serial.println("TEST0");
			s[0]='\0';
			replyPacket[0]='\0';
			convert[3]='\0';
		}
	}
	int len = Udp.read(incomingPacket, 511);
	if (len > 0)
	{/*
	incomingPacket[len] = '\0';
	strcpy(command, Udp.remoteIP().toString().c_str());
	l=strlen(command);
	convert = strcat("###", command); //strcat или strcpy не слагат нулев байт в края на низа
	strcpy(command, convert);
	command[l+3]='\0';
	convert = strcat(command, ";");
	strcpy(command, convert);
	convert = strcat(command, incomingPacket + 3);
	strcpy(command, convert);
	//Serial.println(command);
	*/
	strcpy(command, "###192.168.97.4;R;small_lamp.state;small_lamp.power;big_lamp.on;pechka.on;### ");
	}
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
