<?php
session_start();
include "connect.php";

if(isset($_SESSION['name'])||isset($_SESSION['password'])){
    unset($_SESSION['name']);
	unset($_SESSION['password']);
}

echo 1;

?>