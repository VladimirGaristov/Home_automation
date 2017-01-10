<?php
$ser_port_opt=array('baud'=>9600, 'bits'=>8, 'stop'=>1, 'parity'=>0);
$arduino=dio_open('/dev/ttyACM0', O_RDWR);
dio_tcsetattr($arduino, $ser_port_opt);
dio_write($arduino, 'Q');
usleep(10000);
echo dio_read($arduino, 10);
dio_close($arduino);
?>