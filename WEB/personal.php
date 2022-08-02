<?php
	include "connect.php";
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
			<form metod = "get">
				<button name="logout" type="submit">Выйти из учетной записи</button></form>
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
			</tr>
		</table>
		</div>

        <br><br>
        <h2 align="center">Ваш личный кабинет</h2>

        <div class="personal">
			<div class="personal_header">
				    <b style="margin: 10px 0;">Добро пожаловать в личный кабинет, <?= $_SESSION['user']['FIO']?>!</b><br>
                	<a href="#">Ваш e-mail в системе: <?= $_SESSION['user']['email']?></a><br><br><br>

					<form method="post">
					<button name="change" type="submit">Редактировать данные</button>
					</form>

					<?php 
						if(isset($_POST['change'])){
							$inquery = "SELECT * from user WHERE user.id_user = ".$_SESSION['user']['id']."";
							$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
							$result = mysqli_fetch_assoc($flag);?>
							<form method="post">
							<table>
									<tr><td>ФИО:</td><td><input type="text" name="FIO" value="<?= $result['FIO']?>"></td></tr>
									<tr><td>Логин:</td><td><input type="text" name="login" value="<?= $result['login']?>"></td></tr>
									<tr><td>E-mail:</td><td><input type="text" name="email" value="<?= $result['email']?>"></td></tr>
									<tr><td>Пароль:</td><td><input type="password" name="pwd" placeholder="Введите пароль"></td></tr>
									<tr><td>Подтвердите пароль:</td><td><input type="password" name="pwd_confirm" placeholder="Подтвердите пароль"></td></tr>
							</table>
							<br><button name="confirm" type="submit">Изменить</button>
							</form>
							<?php
						}
						?>
						<?php

						$pwd = $_POST['pwd'];
						$pwd_confirm = $_POST['pwd_confirm'];
						if(isset($_POST['confirm'])){
							if($pwd === $pwd_confirm){
								$pwd = md5($pwd);
								$inquery = "UPDATE user SET FIO = '".$_POST['FIO']."', login = '".$_POST['login']."', email = '".$_POST['email']."', pwd = '".$pwd."' WHERE id_user = '".$_SESSION['user']['id']."'";
								$flag = mysqli_query($link, $inquery) or die("Ошибка изменения!". mysqli_error($link));
							}
							$check = mysqli_query($link,"SELECT * from user WHERE user.id_user = ".$_SESSION['user']['id']."");
							if (mysqli_num_rows($check) > 0){
								$user = mysqli_fetch_assoc($check);
						
								$_SESSION['user'] = [
									"id"=>$user['id_user'],
									"FIO"=>$user['FIO'],
									"login"=>$user['login'],
									"email"=>$user['email'],
									"pwd"=>$user['pwd']
								];
							}
							echo "<center>Ваши изменения сохранены!</center>";
							header('Refresh: 1, URL = personal.php');
						}?>

					<b style="margin: 10px 0;">Чтобы посмотреть все ваши заказы нажмите <a href="orders.php">сюда</a>!</b><br>
			</div>

			<center><div class="personal_cart">
			<b>Моя корзина</b><br><br>
					<?php
					if(isset($_SESSION['order'])){
						foreach ($_SESSION['order'] as $key => $value){
							$inquery = "SELECT user.FIO, exhibition.exhibition_name, tickettype.Name, ticket.ticket_price from cart INNER JOIN ticket ON (cart.id_ticket = ticket.id_ticket) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN exhibition ON (ticket.id_exhibition = exhibition.id_exhibition) INNER JOIN user ON (cart.id_user = user.id_user)";
							$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
						}
						?>
						<br>
						<form method="get">
						<table border = 2><tr><th>ФИО</th><th>Выставка</th><th>Тип билета</th><th>Цена</th><th>Количество</th></tr>
						<?php
						while ($result = mysqli_fetch_assoc($flag)){?>
							<td><?php echo $result['FIO']?></td>
							<td><?php echo $result['exhibition_name']?></td>
							<td><?php echo $result['Name']?></td>
							<td><?php echo $result['ticket_price']?></td>
							<td><input type="text" name="amount" value=1></td>
							</tr>
						<?php
							$price += ($_GET['amount']*$result['ticket_price']);
						}?>
						</table>
						<br><br>
							<button name="add" type="submit">Добавить мой выбор в заказ</button>
							<button name="delete" type="submit">Очистить корзину</button>
						</form>
					<?php 
					}
					else{
						echo "На данный момент в вашей корзине пусто.<br><br><br>";
					}?>
					<br><br><br>
					<?php
					if(isset($_GET['delete'])){
						foreach ($_SESSION['order'] as $key => $value){
							$inquery = "DELETE FROM cart WHERE id_ticket = '".$value."'";
							$flag = mysqli_query($link, $inquery) or die("Ошибка удаления!". mysqli_error($link));
						}
						unset($price);
						unset($_SESSION['order']);
						echo "<br><b>Ваша корзина очищена!</b>";
						header('Refresh: 1, URL = personal.php');
					}

					if(isset($_GET['add'])){
						if(isset($_GET['amount'])){?>
							<br><b>Общая стоимость билетов: <?php echo $price?> руб.</b>
						<?php
						}
						$dat = strtotime('today');
						$inquery = "INSERT INTO `order` (`id_order`, `sum_price`, `Date_order`, `id_user`) VALUES (NULL,'".$price."','".date('y.m.d', $dat)."','".$_SESSION['user']['id']."')";
						$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
						echo "<br><b>Ваш заказ оформлен! Корзина очищена.</b><br>";
						unset($price);
						
						$inquery = "SELECT order.id_order, order.sum_price, order.Date_order, user.FIO FROM `order` INNER JOIN user ON (order.id_user = user.id_user) WHERE order.id_user = '".$_SESSION['user']['id']."'";
						$flag = mysqli_query($link, $inquery) or die("Ошибка!". mysqli_error($link));
						while ($result = mysqli_fetch_assoc($flag)){?>
							</tr>
						<?php
							$_SESSION['id_order'] = $result['id_order'];
						}
						//echo $_SESSION['id_order'];

						foreach ($_SESSION['order'] as $key => $value){
							$inquery = "INSERT INTO  ticketsinorder (N, Amount, id_ticket, id_order) VALUES (NULL,'".$_GET['amount']."','".$value."','".$_SESSION['id_order']."')";
							$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));

							$inquery = "DELETE FROM cart WHERE id_ticket = '".$value."'";
							$flag = mysqli_query($link, $inquery) or die("Ошибка удаления!". mysqli_error($link));
							unset($_SESSION['order']);
						}
						unset($_SESSION['id_order']);
						header('Refresh: 4, URL = personal.php');
					}
					?>
			</div></center>
        </div>
    </div>
</body>
<br><br><br><br><br><br>
<footer style="background: #990000">
		<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
</footer>

</html>