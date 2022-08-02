<?php 
	$host = 'localhost';
	$database = 'mux_db';
	$username = 'muxvl';
	$password = '';
	$link = mysqli_connect($host,$username,$password,$database);
	if(!$link) die("Ошибка соединения с базой данных". mysqli_connect_error());
	
?>
