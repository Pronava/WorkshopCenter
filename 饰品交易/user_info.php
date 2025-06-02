<?php
session_start();
include "connect.php";

$name=$_SESSION['name'];

$user_info="select*from users where ID=$name";
$r=mysqli_query($conn,$user_info);
$r1= mysqli_fetch_array($r);

$image=base64_encode($r1[4]);
$src='data:image/jpg/png;base64,'.$image;

echo $name;

echo "
<a href='javascript:void(0)' class='closebtn' onclick='closeNav()'>&times;</a>
  <div class='overlay-content'>
    <div class='profile'><img src='$src' alter='profile' class='profile' style='border-radius:100%;height:100px;width:100px;'></div>
    </div>
  <div class='overlay-content'>
    <p>Username: $r1[2]</p>
  </div>
  <div class='overlay-content'>
    <p>e-mail: $r1[3]</p>
  </div>
  <div class='overlay-content'>
    <a href='Buyorder.html'>Buy order</a><br>
	<a href='Sellorder.html'>Sell order</a>
	
  </div>
  <div class='overlay-content'>
    <button onclick='quit()'>logout</button> 
  </div>
  </div>
";


?>