<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    try {
        // Establish database connection
        require_once "includes/databaseHandler.inc.php";

        // changes the TINYINT if a user is given a task
        if (isset($_POST['members']) && is_array($_POST['members'])) {
            foreach ($_POST['members'] as $member) {
                $member = mysqli_real_escape_string($connection, $member);

                // Update the database to associate the task with selected team members
                $updatesql = "UPDATE users SET cur_tasks = 1 WHERE name = '$member'";
        
            }
        }

        $mysqli->affected_rows;
        header("Location: index.php");

        exit();
    } catch (PDOException $e) {
        echo "Task Creation Failed: " . $e->getMessage();
    }
} else {
    echo "Invalid request.";
}
