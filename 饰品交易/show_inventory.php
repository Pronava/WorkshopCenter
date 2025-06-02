<?php
session_start();
include "connect.php";
$rows=$_POST['rows'];
$counter=0;

$name=$_SESSION['name'];


$all_inventory="select*from commodity right join store using(com_ID) right join inventory using(inventory_ID) right join users using(ID) where users.ID=$name and com_ID>0";
$r=mysqli_query($conn,$all_inventory);

$result_rows=mysqli_num_rows($r);

if($result_rows<1){
	echo "<p style='color:white;'>EMPTY INVENTORY</p>";
	echo $name;
	return 0;
}


//$r1[2] is commodity_id;

while($r1= mysqli_fetch_array($r)){
	if($counter>=$rows||$counter>=$result_rows) break;
	
	$image=base64_encode($r1[11]);
	$src='data:image/jpg/png;base64,'.$image;
	
	
	echo "
	<div class='card'>
		<div class='card-img'><img src='$src'/></div>
		<div class='card-info'>
			<p class='text-title'>$r1[7]</p>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>wear_rate: $r1[8]</span>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>quality: $r1[9]</span>
		</div>
		<div class='card-footer'>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>price: $r1[10]￥</span>
		<div class='card-button'>
			<button onclick='sell(this.id)' id=$r1[6]>sell</button>
		</div>
		</div>
	</div>
	";
	$counter++;
}

?>