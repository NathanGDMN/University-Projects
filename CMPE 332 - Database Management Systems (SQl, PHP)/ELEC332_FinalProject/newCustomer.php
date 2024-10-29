<!DOCTYPE html>
<html>
<div id="wrapper">
<head>
<meta charset="utf-8">
<title>RestaurantDB</title>
<link rel="stylesheet" type="text/css" href="restaurant.css">
</head>
<body>
<?php
include 'connectdb.php';
?>
<div class="landing">
	<h1>The Restaurant Database</h1>
</div>

<div id="nav">
<ul>
  <li><a class="active" href="restaurant.php">RestaurantDB</a></li>
  <li><a href="viewOrders.php">View Orders</a></li>
  <li><a href="createAcct.php">Create Customer Account</a></li>
  <li><a href="empSchedule.php">View Employee Schedules</a></li>
</ul>
</div>

<ol>
<?php
   $email = $_POST["email"];
   $fname = $_POST["fname"];
   $lname = $_POST["lname"];
   $phone = $_POST["phone"];
   $addr = $_POST["addr"];
   $city = $_POST["city"];
   $post = $_POST["post"];
   
   //Check if customer account already exists
   $query1 = 'SELECT COUNT(*) AS existing FROM customeraccount WHERE emailAddress = "' .$email. '";';
   $result1= $connection->query($query1);
   $row1=$result1->fetch();
   echo $row1["existing"];
   
	if ($row1["existing"] > 0){
		echo " | Error: Email Already in use.";
    } else {
		$query2 = 'INSERT INTO customeraccount VALUES(
			"'.$email.'",
			"'.$fname.'",
			"'.$lname.'",
			"'.$phone.'",
			"'.$addr.'",
			"'.$city.'",
			"'.$post.'",
			"5.00"
		);';
		$numRow = $connection->exec($query2);
		echo " | Your customer account has been created!";
    }
   $connection = NULL;
?>
</ol>
</body>
</html>