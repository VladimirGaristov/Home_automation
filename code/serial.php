<?php

require_once('functions.php');
set_time_limit(0);

$arduino=serial_init(S_PORT_NAME);

cancur($arduino);

dio_close($arduino);

?>