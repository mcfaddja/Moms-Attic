<!DOCTYPE html>
<html>
<body>

<?php
$servername = "localhost";
$username = "jamster";
$password = "1MckiD4";
$dbname = "tempANDrelHsensors";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


echo "Results for the <b><u>testEthernet0</u></b> sensor: <br>";

$sql0 = "SELECT * FROM testEthernet0 ORDER BY measurementID DESC LIMIT 1";
$result0 = $conn->query($sql0);
if ($result0->num_rows > 0) {
    // output data of each row
    while($row0 = $result0->fetch_assoc()) {
        echo "<b>measurementID</b>: " . $row0["measurementID"] . "<br>";
        echo "<b>date</b> : " . $row0[date] . "<br>";
        echo "<b>Relative Humidity</b> : " . $row0[relative_humidity] . "<br>";
        echo "<b>Temperature (C)</b> : " . $row0[temperatureC] . "<br>";
        echo "<b>Temperature (F)</b> : " . $row0[temperatureF] . "<br>";
    }
} else {
    echo "0 results";
}
echo "<br>";


echo "Results for the <b><u>testEthernet1</u></b> sensor: <br>";

$sql1 = "SELECT * FROM testEthernet1 ORDER BY measurementID DESC LIMIT 1";
$result1 = $conn->query($sql1);
if ($result1->num_rows > 0) {
    // output data of each row
    while($row1 = $result1->fetch_assoc()) {
        echo "<b>measurementID</b>: " . $row1["measurementID"] . "<br>";
        echo "<b>date</b> : " . $row1[date] . "<br>";
        echo "<b>Relative Humidity</b> : " . $row1[relative_humidity] . "<br>";
        echo "<b>Temperature (C)</b> : " . $row1[temperatureC] . "<br>";
        echo "<b>Temperature (F)</b> : " . $row1[temperatureF] . "<br>";
    }
} else {
    echo "0 results";
}
echo "<br>";


echo "Results for the <b><u>testEthernet1</u></b> sensor: <br>";

$sql2 = "SELECT * FROM testEthernet2 ORDER BY measurementID DESC LIMIT 1";
$result2 = $conn->query($sql2);
if ($result2->num_rows > 0) {
    // output data of each row
    while($row2 = $result2->fetch_assoc()) {
        echo "<b>measurementID</b>: " . $row2["measurementID"] . "<br>";
        echo "<b>date</b> : " . $row2[date] . "<br>";
        echo "<b>Relative Humidity</b> : " . $row2[relative_humidity] . "<br>";
        echo "<b>Temperature (C)</b> : " . $row2[temperatureC] . "<br>";
        echo "<b>Temperature (F)</b> : " . $row2[temperatureF] . "<br>";
    }
} else {
    echo "0 results";
}


$conn->close();
?>

</body>
</html>