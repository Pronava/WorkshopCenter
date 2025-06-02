<?php
include "connect.php";

$userid = $_POST["userid"];
$passwd = $_POST["password"];
$Name = $_POST["username"];
$pn = $_POST["phone"];
$email = $_POST["email"];
$image =  mysqli_escape_string($conn,file_get_contents($_FILES['profile']['tmp_name']));

$sql1 = "select * from users where ID ='$userid'";
$result1 = mysqli_query($conn, $sql1);
if(mysqli_num_rows($result1) > 0){
    echo "<script>";
    echo "alert('User ID already exist!');";
    echo "window.location.replace('register.html');";
    echo "</script>";
}else{
    $sql = "insert into users values ('$userid', '$passwd', '$Name', '$email','$image')";
    $result = mysqli_query($conn, $sql);
    $insert_phone = "insert into users_phone values ('$userid','$pn');";
	$r0=mysqli_query($conn, $insert_phone);	
	$create_inventory="insert into inventory values ('$userid', '$userid')";
	$r1=mysqli_query($conn, $create_inventory);	
    echo "<script>";
    echo "alert('Register successfully!');";
    echo "window.location.replace('homepage.html');";
    echo "</script>";
}



?>