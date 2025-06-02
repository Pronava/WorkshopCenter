<?php
session_start();
include "connect.php";
$username=$_POST['username'];
$password=$_POST['password'];
$identity=$_POST['identity'];

if($identity=="users"){
	$user="select * from users where ID=$username and password='$password'";
	$r=mysqli_query($conn,$user);
}

else if($identity=="administrator"){
	$admin="select*from administrator where ID=$username and password='$password'";
	$r=mysqli_query($conn,$admin);
}

$rows= mysqli_num_rows($r);

if($rows==0){
	echo 0;
	return 0;
}
else if($rows==1){
	$_SESSION['name']=$username;
	$_SESSION['password']=$password;
	
	if($identity=="users")
		echo 1;
	else if($identity=="administrator")
		echo 2;
}


?>