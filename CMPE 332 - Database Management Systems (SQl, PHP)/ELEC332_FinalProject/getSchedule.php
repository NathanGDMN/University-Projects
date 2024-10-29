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
   $empID= $_POST["emp"];
   //echo $empID;
   
   //Find employee schedule matching empID
   $query1 = 'SELECT * FROM shift WHERE empID ="'.$empID.'" AND (day != "Sunday" OR day!="Saturday") ORDER BY CASE
         WHEN day = "Monday" then 1
         WHEN day = "Tuesday" then 2 
         WHEN day = "Wednesday" then 3
         WHEN day = "Thursday" then 4
         WHEN day = "Friday" then 5
         END ASC;';
   $result1= $connection->query($query1);
   echo "Assigned shifts: <br>";
   echo "<table>";
   echo "<tr><th>"."Days". "</th><th>" . "Start Time" . "</th><th>" . "End Time" . "</th></tr>";
   while ($row = $result1->fetch()) {
	   echo "<tr><td>".$row["day"]. "</td><td>" . $row["startTime"] . "<td>" . $row["endTime"] ."</td></tr>";
   }
   echo "</table>";
   $connection = NULL;
?>
</ol>

<?php
$connection =- NULL;
?>
</body>
</html>