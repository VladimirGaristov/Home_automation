//prototype code
//Added security check for sql injection
//Updated with proper sql commands
//needs to be tested

<?php
   define('DB_SERVER', 'localhost');
   define('DB_USERNAME', 'kompir');
   define('DB_PASSWORD', 'chumbedrum420');
   define('DB_NAME', 'home_automation');
   define('PASSWORD', 'Apple');
   $db = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

   if (mysqli_connect_errno()) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
   }

   $small_lamp = mysqli_real_escape_string($db, $_GET['small_lamp_p']);
   $pechka = mysqli_real_escape_string($db, $_GET['pechka']);
   $big_lamp = mysqli_real_escape_string($db, $_GET['big_lamp']);
   $_password = mysqli_real_escape_string($db, $_GET['password']);

   if ($_password == PASSWORD) {
       if ($small_lamp) {
           $db->query("UPDATE `small_lamp` SET `on` = ".$small_lamp.";");
       }
       if ($pechka) {
           $db->query("UPDATE `pechka` SET `power` = ".$pechka.";");
       }
       if ($big_lamp) {
           $db->query("UPDATE `big_lamp` SET `big_lamp` = ".$big_lamp.";");
       }
   }

   mysql_close($db);
 ?>
