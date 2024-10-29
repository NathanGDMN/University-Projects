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

<h2>About RestaurantDB:</h2>
<p>
The restaurant database is a comprehensive system that efficiently stores and manages information about various restaurants, their employees, and customer accounts. It is designed to ensure seamless operations within the restaurant industry, and it provides easy access to critical data that restaurant owners and managers require to make informed decisions.<br><br>

The database is organized into several tables, with each table dedicated to specific types of data. The restaurant names table contains all the necessary information about the different restaurants in the system, including their names, addresses, contact information, and other pertinent details.<br><br>

The employee information table contains all employee-related data, including the employee's name, contact information, position, salary, and other employment details. This table ensures that restaurants can efficiently manage their workforce by keeping track of employee schedules, wages, and other related information.<br><br>

The customer account information table contains all data related to customer accounts. This includes customer names, addresses, phone numbers, email addresses, and order histories. This table ensures that restaurants can keep track of customer orders and preferences, allowing them to provide personalized service and improve customer satisfaction.
<p>

<?php
$connection =- NULL;
?>
</body>
</div>