<?php
	session_start();
	include "connect.php";
	$searchID=$_POST['searchID'];
	$quality=$_POST['quality'];
	$skin_name=$_POST['skin_name'];
	$wear_rate=$_POST['wear_rate'];
	$price=$_POST['price'];
	$date=date("Y.m.d");
	
	$name=$_SESSION['name'];
	
	$check="select*from manage where com_ID=$searchID and ID=$name";
	$c=mysqli_query($conn,$check);
	if(mysqli_num_rows($c)==1){
		echo "<< you modified it once (select another) >>";
		return 0;
	}
	
	$manage="insert into manage values($searchID,$name,'$date')";
	$m=mysqli_query($conn,$manage);

	
	$update="update commodity set skin_name='$skin_name',quality='$quality',wear_rate=$wear_rate,price=$price,upload_date='$date' where com_ID=$searchID";
	$result= mysqli_query($conn,$update);
	
	if($result&&$m)
		echo "successfully updated";
	else 
		echo "failed";
	
?>