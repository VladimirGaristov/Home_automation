<?php
   define('DB_SERVER', 'localhost');
   define('DB_USERNAME', 'kompir');
   define('DB_PASSWORD', 'chumbedrum420');
   define('DB_NAME', 'home_automation');
   define('PASSWORD', 'Apple'); // static password , needs! to be changed 
   $db = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

   if (mysqli_connect_errno()) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
   }

   $small_lamp = mysqli_real_escape_string($db, $_POST['small_lamp_p']);
   $pechka = mysqli_real_escape_string($db, $_POST['pechka_p']);
   $big_lamp = mysqli_real_escape_string($db, $_POST['big_lamp_p']);
   $_password = mysqli_real_escape_string($db, $_POST['password']);

   if ($_password == PASSWORD) {
       if ($small_lamp != '-') {
           $db->query("UPDATE `small_lamp` SET `value` = ".$small_lamp." WHERE variable_name='power';");
       }
       if ($pechka != '-') {
           $db->query("UPDATE `pechka` SET `value` = ".$pechka." WHERE variable_name='on';");
       }
       if ($big_lamp != '-') {
           $db->query("UPDATE `big_lamp` SET `value` = ".$big_lamp." WHERE variable_name='on';");
       }
   }

   mysqli_close($db);
 ?>
