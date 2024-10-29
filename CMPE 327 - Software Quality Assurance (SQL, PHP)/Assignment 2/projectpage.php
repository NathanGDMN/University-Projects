<?php
    //Create query to show all projects in database
        try {
            require_once "includes/databaseHandler.inc.php";
            //Execute prepared SQL Statement:
            $query = "SELECT * FROM tasks WHERE projectId = 1;";
            $statement = $pdo->prepare($query);
            $statement -> execute();
            $results = $statement->fetchAll(PDO::FETCH_ASSOC);
    
            //Close Connection:
            $pdo = NULL;
            $statement = NULL;
        } catch (PDOException $e) {
            die("Existing Tasks Query Failed: " . $e->getMessage());
        }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <title>Project Manager</title>

    <!-- Link to CSS and JS: -->
    <link rel="stylesheet" href="projectpage.css">
    <script src="app.js"></script>

</head>
<body>
    <button id="createTaskButton" type="button" onclick="toggleTaskCreation()">Create Task</button>

    <div id = "existingTasks">
        <h2>Existing Tasks</h2>

        <?php
            if(empty($results)){
                echo "<p>You have no existing tasks!</p>";
            }else{
                //var_dump($results); //Raw results from query
                echo "<ul id = 'existingTasksList'>";
                foreach($results as $row){
                    echo "<li>";
                    echo htmlspecialchars($row["taskName"]);
                    echo ",  Due: ";
                    echo htmlspecialchars($row["taskDueDate"]);
                    echo ",  Members: ";
                    echo htmlspecialchars($row["taskAssignee"]);
                    echo "</li>";
                }
                echo "</ul>";
            }
        ?>

        <!-- <ul id = "existingTasksList">
            <li><a href="projectpage.html">Task 1</a><p>DueDate: ..... Members:  ....</p></li>
            <li><a href="projectpage.html">Task 2</a><p>DueDate: ..... Members:  ....</p></li>
            <li><a href="projectpage.html">Task 3</a><p>DueDate: ..... Members:  ....</p></li>
        </ul> -->
    </div>

    <div id="createTaskTab" class="createTask">
        <h2>Create New Task</h2>

        <form action="includes/taskFormHandler.inc.php" method="post">
            <label>Name:</label>
            <input type="text" name="taskName" placeholder="Name">
            <br><br>
            <label>DueDate:</label>
            <input type="date" name="dueDate" onClick="dateAssigned()">
            <br><br>
            <label>Assignee:</label>
            <input type="text" name="members">
            <br><br>
            <label>Priority (1-most urgent, 5-least urgent):</label>
            <input type="text" name="taskPriority" placeholder="Priority">
            <br><br>
            <label>Progress (%):</label>
            <input type="text" name="taskProgress" placeholder="Progress">
            <br><br>
            <button>Create Task</button>
            <br><br>
        </form>

        <!--

        <p>Choose the priority level for this task</p>


        <form id="priority" name="priority">

            <input type="radio" id="1" name="priority" value="1">
            <label for="1">1</label><br>
            <input type="radio" id="2" name="priority" value="2">
            <label for="2">2</label><br>
            <input type="radio" id="3" name="priority" value="3">
            <label for="3">3</label><br>
            <input type="radio" id="4" name="priority" value="4">
            <label for="4">4</label><br>
            <input type="radio" id="5" name="priority" value="5">
            <label for="5">5</label><br>

        </form>

        <p>Assign team members to this task</p>

        <form id="teamAssign" name="teamAssign">

            <input type="checkbox" id="member1" name="member1" value="Tom Johnson">
            <label for=member1>Tom Johnson</label><br>
            <input type="checkbox" id="member2" name="member2" value="Jim Johnson">
            <label for=member2>Jim Johnson</label><br>
            <input type="checkbox" id="member3" name="member3" value="Sarah Smith">
            <label for=member3>Sarah Smith</label><br><br>

        </form>

        <button id="closeCreateProjectButton" type="button" onclick="createTaskLink()">Done</button>

        -->

    </div>

</body>
</html>

