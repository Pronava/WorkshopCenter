<?php
session_start();
include "connect.php";

if(!isset($_SESSION['name'])||!isset($_SESSION['password']))
	echo 0;
else if(isset($_SESSION['name'])&&isset($_SESSION['password'])&&$_SESSION['name']<=200000)
	echo 1;
else if(isset($_SESSION['name'])&&isset($_SESSION['password'])&&$_SESSION['name']>200000)
	echo 2;
	

?>