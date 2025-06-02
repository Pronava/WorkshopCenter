<?php
session_start();
include "connect.php";

$name=$_SESSION['name'];
$rows=$_POST['rows'];

$counter=0;

$sell="SELECT * FROM commodity,sell_order WHERE sell_order.com_ID = commodity.com_ID AND sell_order.ID = $name;";

$sell_result= mysqli_query($conn,$sell);

$sell_rows=mysqli_num_rows($sell_result);
if($sell_rows < 1){
	echo "<p style='color:white;'>EMPTY ORDER</p>";
	return 0;
}

while($r1= mysqli_fetch_array($sell_result)){
	if($counter>=$rows) break;

    $image=base64_encode($r1[5]);
	$src='data:image/jpg/png;base64,'.$image;

	echo "
	<div class='news'>
        <div >
		<img class = 'images' src='$src' />
        </div>
        <div class = 'content'>
        <a>Commodity ID: $r1[11]</a><br>
        <a>Skin Name: $r1[1]</a><br>
        <a>Quality: $r1[3]</a><br>
        <a>Wear Rate: $r1[2]</a><br>
        <a>Sell Price: $r1[12]￥</a><br>
        <a>Sell Date: $r1[13]</a>
        </div>
	</div>
	";
	$counter++;
}

?>