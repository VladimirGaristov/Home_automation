<?php

//Изпраща 0 до ардуиното при всяко зареждане на страницата.
echo 'test ';
$arduino=dio_open('/dev/ttyACM0', O_WRONLY);
$ser_port_opt=array('baud'=>9600, 'bits'=>8, 'stop'=>1, 'parity'=>0);
dio_tcsetattr($arduino, $ser_port_opt);
$out='0';
echo dio_write($arduino, $out, 1);
dio_close($arduino);

//echo shell_exec("cat /home/cartogan/Documents/test.txt");

?>