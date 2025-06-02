<?php
$servername = "localhost";
$username 	= "root";
$password 	= "";
$db		    = "csgo";
$conn = new mysqli($servername, $username, $password, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
else
	echo "";
?>
