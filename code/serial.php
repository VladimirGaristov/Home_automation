<?php

require_once('functions.php');
set_time_limit(0);

/*
$arduino=new Serial();
$arduino->init(PORT_NAME);
$arduino->cancur();
$arduino->end();
*/

$db=new mysqli("localhost", DB_USERNAME, DB_PASS, DB_NAME);
if($db->connect_errno)
	exit('Failed to connect to MySQL: ('.$db->connect_errno.') '.$db->connect_error);

$a=new Comm_protocol_action();
$a->command='###192.168.1.4;I;karpuz;###';

if($a->verify()===0)	//Това ще е в цикъл.
{
	$a->get_IP();
	$a->type=$a->command_type();
	if($a->type===1)
		$a->error(4);
	else
	{
		call_user_func(array($a, $a->type));
		if(isset($a->reply))
			echo $a->reply;	//$arduino->write
	}
}
else
	$a->error(1);

?>