<?php
	include "connect.php";
	$deleteID=$_POST['deleteID'];
	
	$search="select*from commodity where com_ID=$deleteID and status<>'in inventory'";
	
	$result= mysqli_query($conn,$search);

	if(mysqli_num_rows($result) < 1){
		echo"<div class='feedback'>";
		echo "<div style='color:gray;font-family:Arial;font-size:25px;margin-top:15px;'>no record</div>";
		echo "<div>";
		return 0;
	}
	
	$row= mysqli_fetch_array($result);
	
	$image=base64_encode($row[5]);
	$src='data:image/jpg/png;base64,'.$image;
	echo "<div style='color:gray;font-family:Arial;margin:5px;'>commodity ID:".$row[0]."</div>";
	echo "<img class='photo' src='$src' ></img>";
	
	echo "<div style='color:gray;font-family:Arial;font-size:25px;margin-top:15px;'>Successfully deleted</div>";
	
	$delete="delete from commodity where com_ID=".$deleteID;
	$t1 = microtime(true);
	$d=mysqli_query($conn,$delete);
	$t2 = microtime(true);
	$timecost=round($t2 - $t1, 3);
	
	echo "<p style='color:gray;font-family:Arial;'>Rough estimate of deleteion request time: ".$timecost."s<br>";
	
?>