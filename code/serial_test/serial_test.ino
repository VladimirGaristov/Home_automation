int button_state=0, prev_button_state=0;

void setup()
{
	pinMode(8, INPUT);
	Serial.begin(9600);
}

void loop()
{
	delay(10);
	prev_button_state=button_state;
	button_state=digitalRead(8);
	if(button_state==HIGH && prev_button_state==LOW)
		Serial.print(1);
	if(button_state==LOW && prev_button_state==HIGH)
		Serial.print(0);
}
