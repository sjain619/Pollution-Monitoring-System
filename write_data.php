<?php

    // Prepare variables for database connection
    // IMPORTANT: if you are using XAMPP enter "localhost", but if you have an online website enter its address, ie."www.yourwebsite.com"

    // Connect to your database

    $dbconnect = mysqli_connect('localhost', 'root', '','testdb');
    

    // Prepare the SQL statement

    $sql = "INSERT INTO testdb.sensordata (arduinoid,kitlocation,gassensor,soundsensor,watersensor) VALUES ('".$_GET["arduinoid"]."','".$_GET["kitlocation"]."','".$_GET["gassensor"]."','".$_GET["soundsensor"]."','".$_GET["watersensor"]."')";    

    // Execute SQL statement

    mysqli_query($dbconnect,$sql);

?>