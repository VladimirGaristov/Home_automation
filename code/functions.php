<?php

const S_PORT_NAME = '/dev/ttyACM0';

function serial_init($port_name)
{
	$ser_port_opt=array('baud'=>9600, 'bits'=>8, 'stop'=>1, 'parity'=>0);
	$arduino=dio_open(S_PORT_NAME, O_RDWR);
	dio_tcsetattr($arduino, $ser_port_opt);
	//usleep(2000);
	return $arduino;
}

function cancur(&$arduino)
{
	dio_write($arduino, '0');
	usleep(50000);
	echo dio_read($arduino, 100);
}

function s_read()
{

}

function s_write()
{

}

function verify()
{

}

function decode()
{

}

function new_module()
{

}

function db_write()
{

}

function db_read()
{

}

function respond()
{

}

?>