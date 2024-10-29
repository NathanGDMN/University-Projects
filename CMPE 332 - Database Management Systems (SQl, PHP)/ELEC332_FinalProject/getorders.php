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

<h1>All orders from entered date:</h1>
<?php
   $inputDate= $_POST["lookupdate"];
   $orderDate=date("Y-m-d",strtotime($inputDate));
	
   //Info for orders on given date:
   $query1 = 'SELECT firstname, lastname, emailAddress, orderID FROM customeraccount RIGHT JOIN orderplacement ON customeraccount.emailAddress = orderplacement.customerEmail WHERE orderDate="'.$orderDate.'";';
   $result1=$connection->query($query1);
    
    while ($row1=$result1->fetch()) { //For each order:
		echo "------------------------------------------------------------<br>";
		//Print firstname and lastname of orderer 
		echo $row1["firstname"]." ".$row1["lastname"]. " | ";
		//Print totalPrice
		$query3  = 'SELECT totalPrice, tip FROM foodorder WHERE orderID = '.$row1["orderID"].'';
		$result3=$connection->query($query3);
		$row3=$result3->fetch();
		echo 'Total Price: $'.$row3["totalPrice"];
		//Find food in order 
		$query2 = 'SELECT customerEmail,food FROM orderplacement LEFT JOIN fooditemsinorder ON orderplacement.orderID = fooditemsinorder.orderID WHERE orderplacement.orderDate = "'.$orderDate.'" AND customerEmail = "'.$row1["emailAddress"].'";';
		$result2=$connection->query($query2);
		//List items(food) in order
		echo "<ul>";
		while ($row2=$result2->fetch()){
			echo "<li>";
			echo $row2["food"]."</li>";
		}
		echo "</ul>";
		//Find delivery driver
		$query4 = 'SELECT firstname, lastname from delivery LEFT JOIN employee ON delivery.deliveryPerson = employee.ID WHERE orderID ='.$row1["orderID"];
		$result4=$connection->query($query4);
		$row4=$result4->fetch();
		echo "Delivery Person: ".$row4["firstname"]." ".$row4["lastname"] . "	";
		echo '| Tip: $'.$row3["tip"]."<br>";
    }
?>

<?php
   $connection = NULL;
?>
</body>
</html>