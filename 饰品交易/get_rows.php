<?php
include "connect.php";

$rows="select count(com_ID) from commodity";
$r=mysqli_query($conn,$rows);
$r1=mysqli_fetch_array($r);
echo $r1[0];

?>