<!DOCTYPE html>
<html>
<?php
session_start();
if(isset($_GET['logout'])){
    session_destroy();
    header('Location: /');
    exit;
}
else{
	session_start();
}
?>

<head>
	<meta charset="utf-8">
	<meta name="keywords" content="HTML,CSS,PHP">
	<title>erarta.museum</title>
	<link rel="stylesheet" href = "css/style.css">
</head>
<body bgcolor="white">
	<header style="background: white;">
		<div class="head" >
			<img class="logo" src="img/logo.jpg" width="360" height="80">
			<center><b style="font-family:Georgia;font-size: 35px;">museum E R A R T A</b></center>
			<div class="ss" style="text-align: right;border: 1px solid #990000;border-radius: 3px;padding: 10px;">
			<?php 
			if(isset($_SESSION['user']['login'])){?>
				<b>Здравствуйте, <?= $_SESSION['user']['FIO'] ?>!</b><br>
				<i>Ваш логин в системе: <?= $_SESSION['user']['login'] ?></i>
			<?php
			}?>
			</div>
			<?php
			if(isset($_SESSION['user']['login'])){?>	
			<form metod = "get"><button name="logout" type="submit">Выйти из учетной записи</button></form>
			<?php
			}?>
		</div>	
	</header>
	<div class="main">

		<div class="navigation">
		<table style="text-align: center;width: 90%;">
			<tr>
				<td><a href="index.php">Главная</a></td>
				<td><a href="afisha.php">Афиша</a></td>
				<td><a href="tickets.php">Билеты</a></td>
				<td><a href="contacts.php">Контакты</a></td>
				<?php 
				if(isset($_SESSION['user']['login'])){?>
				<td><a href="personal.php">моя Эрарта</a></td>
				<?php
				}else{
					?>
					<td><a href="auth.php">моя Эрарта</a></td>
				<?php
				}?>
				</td>
			</tr>
		</table>
		</div>
		<br><br>
		<div class="container">
		<center><b style="font-family:Georgia;font-size: 15px;">Главная страница</b></center><br>
		<center><i style="font-family:Georgia;font-size: 15px;">Сегодня мы работаем с 10:00 до 20:00</i></center>
		<p style="text-align: center;">музей современного искусства Эрарта представляет выставку</p>
		<center><b style="font-family:Courier;font-size: 18px;">ХЕЛЬМУТ НЬЮТОН</b></center>
		<p style="text-align: center;">до 17 мая</p>
			<div class="col">
			<center><img src="img/exhib.jpeg" width="1150" height="390"></center>
			</div>
			<center><div class="col">
			<?php	
			echo "Список актуальных выставок вы можете посмотреть на странице <a href=\"afisha.php\">афиши</a>.<br>
			До скорой встречи!";
			?>
		</div></center>
	</div>
</body>
<br><br><br>
<footer style="background: #990000">
		<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
</footer>
<?php
	include "counter/counter.php";
?>
</html>
