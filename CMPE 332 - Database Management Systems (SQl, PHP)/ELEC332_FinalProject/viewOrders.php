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

<h2>View Orders By Date:</h2>
<form action="getorders.php" method="post">
<input type="date" name="lookupdate">
<input type="submit" value="Find Orders">
</form>

<h2> Number Of Orders By Date:</h2>
<?php
	$query = 'SELECT orderDate,  COUNT(*) AS orderCount FROM orderplacement GROUP BY orderDate HAVING orderCount > 0;';
	$result = $connection->query($query);
	echo "<table>";
	echo "<tr><th>" ."Date". "</th><th>" . "Number of Orders" . "</th></tr>";
	while ($row=$result->fetch()) {
		echo "<tr><td>".$row["orderDate"]."</td><td>".$row["orderCount"]."</td></tr>";
    }
	echo "</table>";
?>

<?php
$connection =- NULL;
?>
</body>
</div>