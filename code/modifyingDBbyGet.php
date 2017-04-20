//prototype code
//Added security check for sql injection
//needs to be tested

<?php
   define('DB_SERVER', 'localhost:3036');
   define('DB_USERNAME', 'kompir');
   define('DB_PASSWORD', 'chumbedrum420');
   define('DB_NAME', 'home_automation');
   $db = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);
  
   if (mysqli_connect_errno()) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
   }

   class ModifyDB {
       private $small_lamp = mysqli_real_escape_string($db, $_GET['small_lamp_p']);
       private $pechka = mysqli_real_escape_string($db, $_GET['pechka']);
       private $big_lamp = mysqli_real_escape_string($db, $_GET['big_lamp']);
       private $_password = mysqli_real_escape_string($db, $_GET['password']);

       public function writing_to_DB() {
          if ($small_lamp) {
              $db->query("INSERT INTO `small_lamp_p` VALUES (".$small_lamp.");");
          }
          if ($pechka) {
              $db->query("INSERT INTO `pechka` VALUES (".$pechka.");");
          }
          if ($big_lamp) {
              $db->query("INSERT INTO `big_lamp` VALUES (".$big_lamp.");");
          }
          if ($_password) {
              $db->query("INSERT INTO `password` VALUES (".$_password.");");
          }
       }

   }
 ?>
