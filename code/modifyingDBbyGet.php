//prototype code
//need to check for query string validity
//needs to be tested

<?php
   define('DB_SERVER', 'localhost:3036');
   define('DB_USERNAME', 'kompir');
   define('DB_PASSWORD', 'chumbedrum420');
   define('DB_NAME', 'home_automation');
   $db = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

   class ModifyDB {
       /*private $small_lamp;
       private $pechka;
       private $big_lamp;
       private $_password;*/

       public function writing_to_DB() {
          if ($_GET['small_lamp_p']) {
              $db->query("INSERT INTO `small_lamp_p` VALUES (".$_GET['small_lamp_p'].");");
          }
          if ($_GET['pechka']) {
              $db->query("INSERT INTO `pechka` VALUES (".$_GET['pechka'].");");
          }
          if ($_GET['big_lamp']) {
              $db->query("INSERT INTO `big_lamp` VALUES (".$_GET['big_lamp'].");");
          }
          if ($_GET['password']) {
              $db->query("INSERT INTO `password` VALUES (".$_GET['password'].");");
          }
       }

   }
 ?>
