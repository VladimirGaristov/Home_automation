void setup()
{
	Serial.begin(9600);
}

void loop()
{

	if(Serial.available() > 0)
		if(Serial.read()==48)
			Serial.println("I habe a cancur.");
		Serial.flush();
		delay(10);
}