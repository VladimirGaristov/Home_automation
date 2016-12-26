/*
Извежда на екрана данните, изпращани серийно от Ардуиното.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arduino-serial-lib.h"

#define BAUDRATE 9600
#define TIMEOUT 5000
#define PORT_NAME "/dev/ttyACM0"

int main()
{
	int a, port=-1;
	a=65;
	port=serialport_init(PORT_NAME, BAUDRATE);
	serialport_flush(port);
	printf("BEGIN\n");
	long int i=0;
	if(port==-1)
	{
		printf("ERROR\ncould not open the port");
		sleep(2);
		return -1;
	}
	while(i<29999999)	//Държи се сякаш цикъла се изпълнява без printf() и след това printf()-ите се изсипват накуп.
	{
		if(read(port, &a, 1)==1)
		{
			printf("%c",a);
		}
		i++;
	}
	return 1;
}