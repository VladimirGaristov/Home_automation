<?php

require_once('functions.php');
set_time_limit(0);

/*
$arduino=new Serial();
$arduino->init(PORT_NAME);
$arduino->cancur();
$arduino->end();
*/

$db=new mysqli(DB_SERVER, DB_USERNAME, DB_PASS, DB_NAME);
if($db->connect_errno)
	exit('Failed to connect to MySQL: ('.$db->connect_errno.') '.$db->connect_error);

$a=new Comm_protocol_action();
$a->command='###192.168.1.5;R;ko6an;kozza.seno;###';

if($a->verify_command()===0)	//Това ще е в цикъл.
{
	$a->get_IP();
	$a->get_module_name();
	$a->command_type();
	if($a->type===FALSE)
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