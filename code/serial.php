<?php

require_once('functions.php');
set_time_limit(0);

$arduino=new Serial();
$arduino->init(S_PORT_NAME);

$db=new mysqli(DB_SERVER, DB_USERNAME, DB_PASS, DB_NAME);
if($db->connect_errno)
	exit('Failed to connect to MySQL: ('.$db->connect_errno.') '.$db->connect_error);

$a=new Comm_protocol_action();

$attemps=5;

while(1)
{
	$attemps--;
	$l=$arduino->read($a->command);
	usleep(DELAY);
	if($attemps==0)
	{
		exit(-1);
	}
	if($l==-1)
	{
		echo '<br>Nothing to read.';
		continue;
	}
	if($a->verify_command())
	{
		echo '<br>Command: '.$a->command;
		$a->get_IP();
		$a->get_module_name();
		$a->command_type();
		if($a->type===FALSE)
			$a->error(4);
		else
		{
			call_user_func(array($a, $a->type));
			if(isset($a->reply))
				$arduino->write($a->reply);
		}
		$a->debug_info();
	}
	else
		$a->error(1);
}

$arduino->end();

?>