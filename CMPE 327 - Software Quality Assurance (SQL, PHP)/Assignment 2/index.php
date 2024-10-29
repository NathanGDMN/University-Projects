<?php
    //Create query to show all projects in database
        try {
            require_once "includes/databaseHandler.inc.php";
            //Execute prepared SQL Statement:
            $query = "SELECT * FROM projects;";
            $statement = $pdo->prepare($query);
            $statement -> execute();
            $results = $statement->fetchAll(PDO::FETCH_ASSOC);
    
            //Close Connection:
            $pdo = NULL;
            $statement = NULL;
        } catch (PDOException $e) {
            die("Existing Project Query Failed: " . $e->getMessage());
        }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <!-- Default HTML Stuff -->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <!-- Link to CSS and JS: -->
    <link rel="stylesheet" href="homepage.css">
    <script src="app.js"></script>
    
    <!-- Tab Title: -->
    <title>Project Manager</title>
</head>
<body>
    <button id="createProjectButton" type="button" onclick="toggleProjectCreation()">Create Project</button>

    <div id = "existingProjects">
        <h2>Existing Projects</h2>

        <?php
            if(empty($results)){
                echo "<p>You have no existing projects!</p>";
            }else{
                //var_dump($results); //Raw results from query
                echo "<ul id = 'existingProjectsList'>";
                foreach($results as $row){
                    echo "<li><a href='projectpage.php'>";
                    echo htmlspecialchars($row["projectName"]);
                    echo "</a>,  Due: ";
                    echo htmlspecialchars($row["projectDueDate"]);
                    echo "</li>";
                }
                echo "</ul>";
            }
        ?>

        <!-- <ul id = 'existingProjectsList'>
            <li><a href="projectpage.php" onclick = 'setProjectView(1)'>Project 1</a></li>
            <li><a href="projectpage.html">Project 2</a></li>
            <li><a href="projectpage.html">Project 3</a></li>
        </ul> -->
    </div>

    <div id="createProjectTab" class="createProject">
        <h2>Create New Project</h2>

        <p>Please fill out project information:</p>

        <form action="includes/projectFormHandler.inc.php" method="post">
            <label>Name:</label>
            <input type="text" name="projectName" placeholder="Name">
            <br><br>
            <label>DueDate:</label>
            <input type="date" name="dueDate" onClick="dateAssigned()">
            <br><br>
            <button>Create Project</button>
            <br><br>
        </form>

        <p>Test</p>
    </div>

</body>
</html>
