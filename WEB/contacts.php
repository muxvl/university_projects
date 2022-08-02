<!DOCTYPE html>
<html>
<?php

session_start();
include "connect.php";
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
	<center><div class="main">
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
		<b style="font-family:Georgia;font-size: 15px;">Aдрес и режим работы</b><br><br><br>
		<i>199106, Россия, Санкт-Петербург, Васильевский остров, 29-я линия, дом 2, музей современного искусства Эрарта</i><br><br><br>
		<i>+ 7 (812) 324 08 09</i><br>
		<i>info@erarta.com</i><br><br><br><br>
		Мы открыты ежедневно, кроме вторника, с 10:00 до 22:00.
		<br><br>

		<b>Вы можете оставить свой отзыв в нашей гостевой книге!</b><br><br>

		<center><div class="guest_book">
			<?php
			$inquery = "SELECT * FROM `guest`";
			$flag = mysqli_query($link, $inquery) or die("Ошибка!". mysqli_error($link));?>
			<form metod = GET>
			<table border = 2><tr><th>Имя гостя</th><th>Дата отзыва</th><th>Сообщение</th></tr>
			<?php
			while ($result = mysqli_fetch_assoc($flag)){?>
				<td><?php echo $result['user']?></td>
				<td><?php echo $result['date']?></td>
				<td><?php echo $result['message']?></td></tr>
			<?php
			}
			?>
			</table>
			<br><button name="add" type="submit">Оставить отзыв</button><br>
			</form>

			<?php
			if(isset($_GET['add'])){?>

				<form method="GET">
				<table>
					<tr><td>Ваше имя:</td><td><input type="text" name="user" value="Введите имя"></td></tr>
					<tr><td>Дата отзыва:</td><td><input type="text" name="date" value="2022-04-23"></td></tr>
					<tr><td>Отзыв:</td><td><input type="text" cols="40" rows="2" name="message" value="Введите текст"></td></tr>
				</table>
				<button name="confirm" type="submit">Отправить</button>
				</form>
				<?php

			}
			if(isset($_GET['confirm'])){
				$inquery = "INSERT INTO `guest`(`id_gb`, `user`, `date`, `message`) VALUES (NULL,'".$_GET['user']."','".$_GET['date']."','".$_GET['message']."')";
				//echo $inquery;
				$flag = mysqli_query($link, $inquery) or die("Ошибка изменения!". mysqli_error($link));
				echo "<center>Ваш отзыв отправлен!</center>";
				header('Refresh: 1, URL = contacts.php');
			}?>
				
		</div></center>

		<form method="post">
		<b>Или напишите нам ваши предложения и пожелания - а мы вам ответим на почту :)</b><br>
    	<textarea name="comment" cols="40" rows="2"></textarea><br>
    	<?php
		if (isset($_SESSION['user']['id'])){?>
			<input type="text" name="guest_mail" value="<?= $_SESSION['user']['email']?>">
			<?php
        	if (isset($_POST["send"])){
            mail($_SESSION["guest_mail"], 'Обратная связь', $_POST["comment"], 'From: info@erarta.com');
        	}
		}
		else{?>
			<input type="text" name="guest_mail" value="Введите ваш e-mail">
			<?php
        	if (isset($_POST["send"])){
				mail($_SESSION["guest_mail"], 'Обратная связь', $_POST["comment"], 'From: info@erarta.com');
        	}
		}
    	?>
    	<button type="submit" name="send">Отправить</button>
		</form>

	</div></center>
	<br><br>
</body>
<footer style="background: #990000">
	<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
	</footer>
</html>
