<?php
include "connect.php";
$rows=$_POST['rows'];
$search=$_POST['search'];
$cate=$_POST['cate'];
$qua=$_POST['qua'];
$counter=0;

/*echo "console.log($search)";
echo "console.log($cate)";
echo "console.log($qua)";*/

$all_coms="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity WHERE status='on sell' ";
$search_coms="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity WHERE skin_name LIKE '%$search%' AND status='on sell'";
$search_cate="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status
 FROM category JOIN com_cat USING(cat_ID) JOIN commodity USING(com_ID) WHERE category.cat_name= '$cate'";
$search_qua="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity WHERE quality='$qua' AND status='on sell'";
$cate_search="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity,(
	SELECT  commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status
 	FROM category JOIN com_cat USING(cat_ID) JOIN commodity USING(com_ID)
	WHERE category.cat_name='$cate')AS a1
 	WHERE commodity.status='on sell' AND commodity.skin_name LIKE '%$search%' AND commodity.com_ID=a1.com_ID";
$cate_qua="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity,(
	SELECT  commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status
 	FROM category JOIN com_cat USING(cat_ID) JOIN commodity USING(com_ID)
	WHERE category.cat_name='$cate')AS a1
 	WHERE commodity.status='on sell' AND commodity.quality='$qua' AND commodity.com_ID=a1.com_ID";
$search_qua="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity,(
	SELECT  commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status
 	FROM commodity
	WHERE commodity.quality='$qua')AS a1
 	WHERE commodity.status='on sell' AND commodity.skin_name LIKE '%$search%' AND commodity.com_ID=a1.com_ID";
$insect="SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, commodity.status FROM commodity,(
	SELECT  commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, 				commodity.status
 	FROM commodity,(
     SELECT commodity.com_ID, commodity.skin_name, commodity.wear_rate, commodity.quality, commodity.price, commodity.photo, commodity.upload_user, commodity.upload_date, 			commodity.status
     FROM commodity JOIN com_cat USING (com_ID) JOIN category USING (cat_ID)
     WHERE category.cat_name='$cate')AS a2
	WHERE commodity.quality='$qua' AND a2.com_ID=commodity.com_ID)AS a1
WHERE commodity.status='on sell' AND commodity.skin_name LIKE '%$search%' AND commodity.com_ID=a1.com_ID";


if($search==""&&$cate=="ALL"&&$qua=="ALL"){	
	$t1 = microtime(true);
	$r=mysqli_query($conn,$all_coms);//全部搜索
	$t2 = microtime(true);
}
if($search==""&&($cate!="ALL"||$qua!="ALL")){
	if($cate!="ALL"&&$qua=="ALL"){//cate搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$search_cate);
		$t2 = microtime(true);
	}
	if($cate=="ALL"&&$qua!="ALL"){//qua搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$search_qua);
		$t2 = microtime(true);
	}
	if($cate!="ALL"&&$qua!="ALL"){//cate+qua搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$cate_qua);
		$t2 = microtime(true);
	}
}
if($search !=""&&$cate=="ALL"&&$qua=="ALL"){//search搜索
	$t1 = microtime(true);
	$r=mysqli_query($conn,$search_coms);
	$t2 = microtime(true);
}
if($search!=""&&($cate!="ALL"||$qua!="ALL")){
	if($cate!="ALL"&&$qua=="ALL"){//search+cate搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$search_cate);
		$t2 = microtime(true);
	}
	if($cate=="ALL"&&$qua!="ALL"){//search+qua搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$search_qua);
		$t2 = microtime(true);
	}
	if($cate!="ALL"&&$qua!="ALL"){//search+cate+qua搜索
		$t1 = microtime(true);
		$r=mysqli_query($conn,$insect);
		$t2 = microtime(true);
	}
}

$timecost=round($t2 - $t1, 3);//计算搜索耗时
// echo"
// 	<script>
// 	alert('search query timecost(microtime):$timecost s');
// 	</script>
// ";
echo "<div class='card' style='grid-column: 1 / span 4;height:10px;width:92%;padding:30px;'>Search query timecost(microtime): $timecost</div>";//输出

//$r=mysqli_query($conn,$all_coms);

$row=mysqli_num_rows($r);

if($row<1) return 0;

while($r1= mysqli_fetch_array($r)){
	if($counter>=$rows) break;
	
	$image=base64_encode($r1[5]);
	$src='data:image/jpg/png;base64,'.$image;
	
	echo "
	<div class='card'>
		<div class='card-img'><img src='$src'/></div>
		<div class='card-info'>
			<p class='text-title'>$r1[1]</p>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>wear_rate: $r1[2]</span>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>quality: $r1[3]</span>
		</div>
		<div class='card-footer'>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>price: $r1[4]￥</span>
		<div class='card-button'>
			<button onclick='buy(this.id)' id=$r1[0] >buy</button>
		</div>
		</div>
	</div>
	";
	$counter++;
}

/*

include "connect.php";
$rows=$_POST['rows'];
$counter=0;

$all_coms="select*from commodity where status='on sell'";
$r=mysqli_query($conn,$all_coms);

while($r1= mysqli_fetch_array($r)){
	if($counter>=$rows) break;
	
	$image=base64_encode($r1[5]);
	$src='data:image/jpg/png;base64,'.$image;
	
	echo "
	<div class='card'>
		<div class='card-img'><img src='$src'/></div>
		<div class='card-info'>
			<p class='text-title'>$r1[1]</p>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>wear_rate: $r1[2]</span>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>quality: $r1[3]</span>
		</div>
		<div class='card-footer'>
			<span class='text-body'><i class='iconfont icon-meiyuanqian'></i>price: $r1[4]</span>
		<div class='card-button'>
			<button onclick='buy(this.id)' id=$r1[0] >buy</button>
		</div>
		</div>
	</div>
	";
	$counter++;
}
*/

?>