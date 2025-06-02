<?php
include "connect.php";

$sql = "select count(*) from commodity";
$result = mysqli_query($conn,$sql);
$row= mysqli_fetch_array($result);

echo "remain items: ".$row[0];

?>