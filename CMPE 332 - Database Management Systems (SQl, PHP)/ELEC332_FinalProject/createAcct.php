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

<h2> Create New Customer Account:</h2>
<form action="newCustomer.php" method="post">
Email Address: <input type="text" name="email"><br>
First Name: <input type="text" name="fname"><br>
Last Name: <input type="text" name="lname"><br>
Phone Number: <input type="text" name="phone"><br>
Street Address: <input type="text" name="addr"><br>
City: <input type="text" name="city"><br>
Postal Code: <input type="text" name="post"><br>
<input type="submit" value="Sign Up">
</form>
<?php
$connection =- NULL;
?>
</body>
</div>