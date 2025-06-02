<?php
	include "connect.php";
	
	$news=$_POST['news'];
	
	$all_info="select*from information";
	$r=mysqli_query($conn,$all_info);
	$rows=mysqli_num_rows($r);
	$ID=$rows+1;
	$sql="insert into information values($ID,'$news')";
	$result=mysqli_query($conn,$sql);
	
	if($result)
		echo "success";
?>