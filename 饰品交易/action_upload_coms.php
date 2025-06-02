<?php
session_start();

include "connect.php";
$name=$_SESSION['name'];
$skin = $_POST["skin"];
$wear = $_POST["wear"];
$price = $_POST["price"];
$date = date("Y-m-d");
$cat = $_POST["category"];
$image =  mysqli_escape_string($conn,file_get_contents($_FILES['profile']['tmp_name']));

if($wear <= 0 || $wear >= 1){
    echo "<script>";
    echo "alert('The wear rate must be a decimal between 0 and 1!');";
    echo "window.location.replace('upload.html');";
    echo "</script>";
}else{
    if($wear > 0 && $wear <= 0.07){
        $quality = "Factory New";
    }
    if($wear > 0.07 && $wear <= 0.15){
        $quality = "Minimal Wear";
    }
    if($wear > 0.15 && $wear <= 0.38){
        $quality = "Field-Tested";
    }
    if($wear > 0.38 && $wear <= 0.45){
        $quality = "Well-Worn";
    }
    if($wear > 0.45 && $wear < 1){
        $quality = "Battle-Scarred";
    }
    
    $sql = "insert into commodity values (0,'$skin',$wear,'$quality',$price,'$image','$name','$date','in inventory')";
    $result = mysqli_query($conn, $sql);
    
    if($result){
        $check = "T";
    }else{
        $check = "F";
    }
    $sql1 = "insert into com_cat 
                select com_ID, cat_ID
                from commodity, category
                where skin_name = '$skin'
                and wear_rate = '$wear'
                and quality = '$quality'
                and price = $price
                and upload_user = '$name'
                and upload_date = '$date'
                and cat_name = '$cat'";
    $result1 = mysqli_query($conn, $sql1);
    
    if($result1){
        $check = "T";
    }else{
        $check = "F";
    }
    
    if($check == "T"){
        echo "<script>";
        echo "alert('Upload commodity successfully!');";
        echo "window.location.replace('inventory.html');";
        echo "</script>";
    }else{
        echo "<script>";
        echo "alert('Upload commodity failed!');";
        echo "window.location.replace('upload.html');";
        echo "</script>";
    }
}


?>