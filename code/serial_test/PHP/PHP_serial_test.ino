int a=-1, b=-1, on=LOW;

void setup()
{
	Serial.begin(9600);
	pinMode(10, OUTPUT);
}

void loop()
{
	b=a;
	a=Serial.read();
	if(a==48 && b!=48)
		if(on==LOW)
			on=HIGH;
		else
			on=LOW;
	digitalWrite(10, on);
}