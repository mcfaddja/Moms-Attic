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
echo "Connected successfully <br>";
echo "<br>";

$sql = "SELECT DISTINCT sensorID from allTestSensors";
$result = $conn->query($sql);

echo "Possible <b><u>sensorID</u></b> values: <br>";
if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<b>sensorID</b>: " . $row["sensorID"]. "<br>";
    }
} else {
    echo "0 results";
}

//$conn->close();
?>

</body>
</html>