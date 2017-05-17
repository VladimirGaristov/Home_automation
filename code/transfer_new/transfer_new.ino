#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

const char* ssid="VIVACOM";
const char* password="22334455";
const int port_out=20200;
const int port_in=20200;

WiFiUDP Udp;
char s_php[1023]="###192.168.1.3;R;theboss.a;anothermodule.avariable;###", s_wifi[1023];
int i,l, ll, j;
char ip[16];
byte ip_bin[4];
int packetSize, len;
char lenght[4];

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
	Udp.begin(port_in);
	Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), port_in);
}

void loop()
{
	if(Serial.available() > 0)
	{
		i=Serial.readBytesUntil('\0', s_wifi, 510);
		s_wifi[i]='\0';
		if (!(strcmp(s_wifi, "?")))
		{
			l=strlen(s_php);
      ll=l;
			for(i=0;i<4;i++)
			{
				lenght[3-i]=l%10+48;
				l/=10;
			}
		  Serial.print(lenght);
      if(ll)
      {
        j=0;
        while(ll>25)
        {
          while(!(Serial.available() > 0));
          Serial.readBytesUntil('\0', s_wifi, 510);
          s_wifi[i]='\0';
          if(!(strcmp(s_wifi, "?")))
          {
            for(i=0;i<25;i++)
            {
              Serial.print(s_php[j*25+i]);
            }
            ll-=25;
          j++;
          }
        }
        while(!(Serial.available() > 0));
        Serial.readBytesUntil('\0', s_wifi, 510);
        s_wifi[i]='\0';
        if(!(strcmp(s_wifi, "?")))
        {
          for(i=0;i<ll;i++)
          {
            Serial.print(s_php[j*25+i]);
          }
        }
				s_php[0]='\0';
			}
		}
		else
		{
			strcpy(s_php, s_wifi);
			l=strlen(s_wifi);
			s_php[l]='\0';
			php_to_wifi();
			parseBytes(ip, '.', ip_bin, 4, 10);
			Udp.beginPacket(ip, port_out);
			Udp.write(s_wifi, strlen(s_wifi));
			Udp.endPacket();
      s_php[0]='\0';
		}
	}
	packetSize = Udp.parsePacket();
	len = Udp.read(s_wifi, 511);
	if(len > 0)
	{
		s_wifi[len] = '\0';
		strcpy(ip, Udp.remoteIP().toString().c_str());
		wifi_to_php();
	}
}

void php_to_wifi()
{
	for(i=0;i<3;i++)
	{
		s_wifi[i]=s_php[i];
	}
	while(s_php[i]!=';')
	{
		ip[i-3]=s_php[i];
		i++;
	}
	ip[i-3]='\0';
	i++;
	l=strlen(ip)+1;
	while(s_php[i]!='\0')
	{
		s_wifi[i-l]=s_php[i];
		i++;
	}
	s_wifi[i-l]='\0';
}

void wifi_to_php()
{
	l=strlen(ip);
	for(i=0;i<3;i++)
	{
		s_php[i]=s_wifi[i];
	}
	while(i<l+3)
	{
		s_php[i]=ip[i-3];
		i++;
	}
	s_php[i]=';';
	i++;
	while(s_wifi[i-l-1]!='\0')
	{
		s_php[i]=s_wifi[i-l-1];
		i++;
	}
	s_php[i]='\0';
}

void parseBytes(const char* str, char sep, byte* bytes, int maxBytes, int base)		//from Stack_Overflow
{
	for (int i = 0; i < maxBytes; i++)
	{
		bytes[i] = strtoul(str, NULL, base);  // Convert byte
		str = strchr(str, sep);               // Find next separator
		if (str == NULL || *str == '\0')
		{
			break;                            // No more separators, exit
		}
		str++;                                // Point to next character after separator
	}
}
