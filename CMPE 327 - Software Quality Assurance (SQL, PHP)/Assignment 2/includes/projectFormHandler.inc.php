<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $projectName = $_POST["projectName"];
    $projectDueDate = $_POST["dueDate"];

    // isset() checks that the variable has been declared and is not null
    if (!isset($projectName)) {
        die("Project name cannot be blank.");
    }

    elseif (!isset($projectDueDate)) {
        die("Project due date cannot be blank.");
    }

    // check if the due date is before the current date, i.e., in the past
    elseif ($projectDueDate < time('now')) {
        die("Project due date cannot be before the current date.");
    }

    try {
        require_once "databaseHandler.inc.php";
        //Execute prepared SQL Statement:
        $query = "INSERT INTO projects (projectName, projectDueDate) VALUES (:projectName, :projectDueDate);";
        $statement = $pdo->prepare($query);
        $statement->bindParam(":projectName", $projectName);
        $statement->bindParam(":projectDueDate", $projectDueDate);
        $statement -> execute();

        //Close Connection:
        $pdo = NULL;
        $statement = NULL;
        header("Location: ../index.php"); //Send user back to main page
        die();
    } catch (PDOException $e) {
        die("Project Creation Failed: " . $e->getMessage());
    }
} else {
    //If user arrives at this file but not through the form, send themback to main page
    header("Location: ../index.php");
}