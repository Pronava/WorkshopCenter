<?php
include "connect.php";
$rows=$_POST['rows'];
$counter=0;

$all_info="select*from information order by i_ID desc";
$r=mysqli_query($conn,$all_info);

while($r1= mysqli_fetch_array($r)){
	if($counter>=$rows) break;

	echo "
	<div class='news'>
		<span>$r1[1]</span>
	</div>
	";
	$counter++;
}

?>