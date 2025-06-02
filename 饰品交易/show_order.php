<?php
session_start();
include "connect.php";

$name=$_SESSION['name'];

$buy="select * from buy_order where ID=$name";
$sell="select * from sell_order where ID=$name";

$buy_result = mysqli_query($conn,$buy);
$sell_result= mysqli_query($conn,$sell);

$buy_rows=mysqli_num_rows($buy_result);
$sell_rows=mysqli_num_rows($sell_result);
if($sell_rows<1&&$buy_rows<1){
	echo "<p style='color:white;'>EMPTY ORDER</p>";
	return 0;
}

echo "<div class='orderBox' style='height:100%;text-align:center;overflow:scroll;'>";

while($r1= mysqli_fetch_array($buy_result)){
	$com="select*from commodity where com_ID=$r1[2]";
	$com_result=mysqli_query($conn,$com);
	$r=mysqli_fetch_array($com_result);
	$image=base64_encode($r[5]);
	$src='data:image/jpg/png;base64,'.$image;
	
	echo "<img src='$src' style='height:150px;width:150px;'></img>";
	echo "<p>purchase cost:".$r1[3]."date: ".$r1[4]."</p>";
	
}

while($r1= mysqli_fetch_array($sell_result)){
	$com="select*from commodity where com_ID=$r1[2]";
	$com_result=mysqli_query($conn,$com);
	$r=mysqli_fetch_array($com_result);
	$image=base64_encode($r[5]);
	$src='data:image/jpg/png;base64,'.$image;
	
	echo "<img src='$src' style='height:150px;width:150px;'></img>";
	echo "<p>selling price:".$r1[3]."date: ".$r1[4]."</p>";

}


echo "<button onclick='user_info()'>back</button>";

echo "</div>";

?>