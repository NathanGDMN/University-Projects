<!-- Connecting a local database to application -->
<?php
try {
    $connection = new PDO('mysql:host=localhost;dbname=restaurantdb', "root", "");
} catch (PDOException $e) {
    print "Error!: ". $e->getMessage(). "<br/>";
    die();
}
?>