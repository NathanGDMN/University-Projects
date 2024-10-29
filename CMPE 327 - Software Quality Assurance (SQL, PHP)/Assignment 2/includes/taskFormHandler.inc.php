<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $projectId = 1;
    $taskName = $_POST["taskName"];
    $taskDueDate = $_POST["dueDate"];
    $taskAssignee = $_POST["members"];
    $taskPriority = $_POST["taskPriority"]
    $taskProgress = $_POST["taskProgress"]

    // isset() checks that the variable has been declared and is not null
    if (!isset($taskName)) {
        die("Task name cannot be blank.");
    }

    elseif (!isset($taskDueDate)) {
        die("Task due date cannot be blank.");
    }

    // check if the due date is before the current date, i.e., in the past
    elseif ($taskDueDate < time('now')) {
        die("Task due date cannot be before the current date.");
    }

    elseif (!isset($taskAssignee)) {
        die("You must assign at least one member to this task!");
    }

    elseif (!isset($taskPriority)) {
        die("Task must have a priority level.");
    }

    // check that the priority level is within bounds
    elseif ($taskPriority < 1 || $taskPriority > 5) {
        die("Priority level must be within the numbers 1-5.");
    }

    // check that the progress level is within bounds
    elseif ($taskProgress < 0) {
        die("Progress precentage cannot be negative.");
    }

    elseif ($taskProgress > 100) {
        die("Progress precentage cannot exceed 100.");
    }

    // if progress level is blank, assume 0 to prevent errors. don't use isset() because it also checks for variable declaration
    elseif ($taskProgress == null) {
        $taskProgress = 0;
    }

    
    try {
        require_once "databaseHandler.inc.php";
        //Execute prepared SQL Statement:
        $query = "INSERT INTO tasks (projectId, taskName, taskDueDate, taskAssignee, taskPriority, TaskProgress) VALUES (:projectId, :taskName, :taskDueDate, :taskAssignee, :taskPriority, :taskProgress);";
        $statement = $pdo->prepare($query);
        $statement->bindParam(":projectId", $projectId);
        $statement->bindParam(":taskName", $taskName);
        $statement->bindParam(":taskDueDate", $taskDueDate);
        $statement->bindParam(":taskAssignee", $taskAssignee);
        $statement->bindParam(":taskPriority", $taskPriority);
        $statement->bindParam(":taskProgress", $taskProgress);
        $statement -> execute();

        //Close Connection:
        $pdo = NULL;
        $statement = NULL;
        header("Location: ../projectpage.php"); //Send user back to project page
        die();
    } catch (PDOException $e) {
        die("Task Creation Failed: " . $e->getMessage());
    }
} else {
    //If user arrives at this file but not through the form, send themback to project page
    header("Location: ../projectpage.php");
}