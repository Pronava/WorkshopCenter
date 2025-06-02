<?php
	include "connect.php";
	$rows=$_POST['rows'];
	$counter=0;
	
	$buy="select * from buy_order";
	$sell="select * from sell_order";
	$avg_buy="select avg(buy_price) from buy_order";
	$avg_sell="select avg(sell_price) from sell_order";
	
	$buy_result = mysqli_query($conn,$buy);
	$sell_result= mysqli_query($conn,$sell);
	
	while($r1= mysqli_fetch_array($buy_result)){
		if($counter>=$rows) break;
			
		$com="select*from commodity where com_ID=$r1[2]";
		$com_result=mysqli_query($conn,$com);
		$r=mysqli_fetch_array($com_result);
		$image=base64_encode($r[5]);
		$src='data:image/jpg/png;base64,'.$image;
		echo "<div class='VTI-item' >";
		echo "<div style='font-family:Arial;font-size:20px;'>Commodity ID:".$r[0]."</div>";
		echo "<img class='VTI_photo' src='$src' ></img>";
		
		$user="select*from users where ID=$r1[1]";
		$user_result= mysqli_query($conn,$user);
		$r0=mysqli_fetch_array($user_result);
		$profile=base64_encode($r0[4]);
		$head_img='data:image/jpg/png;base64,'.$profile;
		echo "<div style='color:gray;font-family:Arial;font-size:20px;'>BUYER: </div><img class='head_img' src='$head_img' tabindex='1'></img>";
		echo "<div class='user-info' id='user-info'> user name: ".$r0[2]." email: <a href =' mailto: $r0[3]'>$r0[3]</a></div>";
		
		echo "<p>price: <i class='fa-solid fa-dollar-sign'></i>".$r1[3]." date: <i class='fa-solid fa-calendar-days'></i> ".$r1[4]."</p></div>";
		
		$counter++;
	}
	$Ravg_buy=mysqli_query($conn,$avg_buy);
	$ravg0= mysqli_fetch_array($Ravg_buy);
	echo "<div class='VTI-item2'><p> average purchase price: <i class='fa-solid fa-dollar-sign'></i> ".$ravg0[0]."</p></div>";
	

	while($r2= mysqli_fetch_array($sell_result)){
		if($counter>=$rows) break;
			
		$com="select*from commodity where com_ID=$r2[2]";
		$com_result=mysqli_query($conn,$com);
		$r=mysqli_fetch_array($com_result);
		$image=base64_encode($r[5]);
		$src='data:image/jpg/png;base64,'.$image;
		echo "<div class='VTI-item'>";
		echo "<div style='font-family:Arial;font-size:20px;'>Commodity ID:".$r[0]."</div>";
		echo "<img class='VTI_photo' src='$src' ></img>";
		
		$user="select*from users where ID=$r2[1]";
		$user_result= mysqli_query($conn,$user);
		$r0=mysqli_fetch_array($user_result);
		$profile=base64_encode($r0[4]);
		$head_img='data:image/jpg/png;base64,'.$profile;
		echo "<div style='color:gray;font-family:Arial;font-size:20px;'>SELLER: </div><img class='head_img' src='$head_img' tabindex='1'></img>";
		echo "<div class='user-info' id='user-info'> user name: ".$r0[2]." email: <a href =' mailto: $r0[3]'>$r0[3]</a></div>";
		
		echo "<p>price: <i class='fa-solid fa-dollar-sign'></i> ".$r2[3]." date: <i class='fa-solid fa-calendar-days'></i> ".$r2[4]."</p></div>";
		
		$counter++;
	}
	
	$Ravg_sell=mysqli_query($conn,$avg_sell);
	$ravg1= mysqli_fetch_array($Ravg_sell);
	echo "<div class='VTI-item2'><p> average selling price: <i class='fa-solid fa-dollar-sign'></i> ".$ravg1[0]."</p></div>";
	
	echo "<button onclick='more()' class='aButtom' style='color:gray;font-family:Arial;margin:5px;padding:5px;'>MORE</button>
		<button onclick='recovery()' class='aButtom' style='color:gray;font-family:Arial;margin:5px;padding:5px;'>RECOVERY</button>";
	
	
?>