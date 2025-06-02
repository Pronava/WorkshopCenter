<?php
session_start();
include "connect.php";
$com_ID=$_POST['com_ID'];

$name=$_SESSION['name'];

$com="select*from commodity where com_Id=$com_ID";
$result=mysqli_query($conn,$com);

$row=mysqli_fetch_array($result);

$sell="insert into sell_order values(0,$name,$com_ID,$row[4],$row[7])";
$r=mysqli_query($conn,$sell);

echo $r;

?>