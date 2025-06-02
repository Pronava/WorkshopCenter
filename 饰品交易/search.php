<?php
	include "connect.php";
	$searchID=$_POST['searchID'];
		
	$search="select*from commodity where com_ID=".$searchID." and status= 'on sell' ";
	$t1 = microtime(true);
	$result= mysqli_query($conn,$search);
	$t2 = microtime(true);
	$timecost=round($t2 - $t1, 3);
	
	$row_num=mysqli_num_rows($result) ;
	if($row_num < 1){
		echo"<div class='feedback'>";
		echo "<div style='color:gray;font-family:Arial;font-size:25px;margin-top:15px;'>no record</div>";
		echo "<div>";
		return 0;
	}
	
	$row= mysqli_fetch_array($result);
	
	$image=base64_encode($row[5]);
	$src='data:image/jpg/png;base64,'.$image;
	
	echo"<div class='feedback'>";
	echo "<div style='color:gray;font-family:Arial;font-size:20px;padding-top:20px;'>DETAILS</div>";
	echo "<div style='color:gray;'>
	<div><span style='margin-right:60px;'>commodity ID: ".$row[0]."</span><span> skin name: ".$row[1]."</span></div>
	<div><span style='margin-right:60px;'>quality: ".$row[3]."</span><span> wear rate: ".$row[2]."</span></div>
	<div><span style='margin-right:60px;'>price: <i class='fa-solid fa-dollar-sign'></i> ".$row[4]."</span><span> date: <i class='fa-solid fa-calendar-days'></i> ".$row[7]."</span></div></div>";
	
	echo "<br><img class='photo' src='$src' ></img>";
	echo "</div>";

	
	$user="select * from users where ID=".$row[6];
	$su= mysqli_query($conn,$user);
	$ru= mysqli_fetch_array($su);
	$profile=base64_encode($ru[4]);
	$head_img='data:image/jpg/png;base64,'.$profile;
	
	echo "<br><div style='color:gray;font-family:Arial;font-size:20px;'>UPLOAD USER:</div><img class='head_img' src='$head_img' tabindex='1'></img>";
	echo "<div class='user-info' id='user-info'> user name: ".$ru[2]." email: <a href =' mailto: $ru[3]'>$ru[3]</a></div>";
	
	echo "<br><p style='color:gray;font-family:Arial;'>Rough estimate of search request time: ".$timecost."s<br>";
	echo "<button onclick='unlock_modify()' class='aButtom' style='color:gray;font-family:Arial;margin-top:5px;padding:5px;'>Correct product information</button>";
	echo "<div style='text-align:center;font-family:Arial;color:purple;font-size:10px;padding-bottom:10px;'><< only one chance >></div>";
	
?>