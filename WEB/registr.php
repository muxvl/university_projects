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
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href = "css/style.css">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>erarta.museum</title>
</head>
<body bgcolor ="white">
<?php 
include "addition.php";
?>
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
	</div>
<br><br>       
<center><div>
    <h2 align="center">Регистрация</h2>
    <form action="signup.php" method="post" height="30vh">
                <label>ФИО</label>
                <input type="text" name="FIO" placeholder="Введите свое полное ФИО">
                <label>Логин</label>
                <input type="text" name="login" placeholder="Введите свой логин">
                <label>E-mail</label>
                <input type="email" name="email" placeholder="Введите свой e-mail">
                <label>Пароль</label>
                <input type="password" name="pwd" placeholder="Введите пароль">
                <label>Подтвердите пароль</label>
                <input type="password" name="pwd_confirm" placeholder="Подтвердите пароль">
                <button type="submit">Зарегистрироваться</button>
                <p>
                    У вас уже есть аккаунт? - <a href="auth.php">авторизируйтесь</a>
                </p>
				<?php  
				if ($_SESSION['msg']){
					echo '<p class="msg"> '.$_SESSION['msg'].'</p>';
				}
				unset($_SESSION['msg']);
				?>
</div>

</body>
<br><br><br><br><br><br><br><br>
<footer style="background: #990000">
		<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
</footer>
</html>
