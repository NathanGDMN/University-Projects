<?php
   $query = "SELECT firstName, lastName, ID FROM employee";
   $result = $connection->query($query);
   echo "Who are you looking up? </br>";
   while ($row = $result->fetch()) {
        echo '<input type="radio" name="emp" value=';
        echo $row["ID"];
        echo '>' . $row["firstName"]." ".$row["lastName"] . "<br>";
   }
?>