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
			</tr>
		</table>
		</div>

        <br><br>
        <h2 align="center">Ваш личный кабинет</h2>

        <div class="personal">
			<div class="personal_header">
				    <b style="margin: 10px 0;">Добро пожаловать в личный кабинет, <?= $_SESSION['user']['FIO']?>!</b><br>
                	<a href="#">Ваш e-mail в системе: <?= $_SESSION['user']['email']?></a><br><br><br>
					<b style="margin: 10px 0;">Чтобы вернуться к корзине нажмите <a href="personal.php">сюда</a>!</b><br>
			</div>
			<center><div class="personal_orders">
			<b>Мои заказы</b><br><br>
					<?php
						$inquery = "SELECT order.id_order, order.sum_price, order.Date_order, user.FIO FROM `order` INNER JOIN user ON (order.id_user = user.id_user) WHERE order.id_user = '".$_SESSION['user']['id']."'";
						$flag = mysqli_query($link, $inquery) or die("Ошибка!". mysqli_error($link));?>
						<form metod = GET>
						<table border = 2><tr><td>Выберите</td><td>ID заказа</td><td>Общая стоимость</td><td>Дата заказа</td><td>Пользователь</td></tr>
						<?php
						while ($result = mysqli_fetch_assoc($flag)){
							echo "<td><input type=\"radio\" name=\"num\" value=\"".$result['id_order']."\"></td>"?>
							<td><?php echo $result['id_order']?></td>
							<td><?php echo $result['sum_price']?> руб.</td>
							<td><?php echo $result['Date_order']?></td>
							<td><?php echo $result['FIO']?></td>
							</tr>
						<?php
							//$id_order = $result['id_order'];
						}
						?>
						</table>
						<input type="submit" name="del" value="Удалить заказ">
						<input type="submit" name="ok" value="Посмотреть подробнее"><br>
						</form>
						<?php
						if(isset($_GET['ok'])){
							if(!empty($_GET['num'])){
								//$_SESSION['num'] = $_GET['num'];
								$inquery = "SELECT ticketsinorder.id_order, tickettype.Name, exhibition.exhibition_name, ticket.ticket_price, ticketsinorder.Amount FROM ticketsinorder INNER JOIN ticket ON (ticketsinorder.id_ticket = ticket.id_ticket) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN exhibition ON (ticket.id_exhibition = exhibition.id_exhibition) WHERE ticketsinorder.id_order = '".$_GET['num']."'";
								$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));?>

								<table border = 2><tr><td>ID заказа</td><td>Тип билета</td><td>Выставка</td><td>Цена билета</td><td>Кол-во билетов</td></tr>
                            	<?php
                            	while ($result = mysqli_fetch_assoc($flag)){?>
                                	<td><?php echo $result['id_order']?></td>
                                	<td><?php echo $result['Name']?></td>
									<td><?php echo $result['exhibition_name']?></td>
									<td><?php echo $result['ticket_price']?></td>
                                	<td><?php echo $result['Amount']?></td>
                                	</tr>
                            	<?php
                           		}?>
                            	</table>
                            <?php
                        	}
							else{
								echo"<b>Выберите заказ для просмотра!</b>";
							}
						}
						if(isset($_GET['del'])){
							if(!empty($_GET['num'])){
								//echo $_GET['num'];
								$inquery = "DELETE FROM `order` WHERE `order`.`id_order` = '".$_GET['num']."' ";
								$flag = mysqli_query($link, $inquery) or die("Ошибка удаления!". mysqli_error($link));

								//$inquery = "DELETE FROM ticketsinorder WHERE order.id_order = ".$_GET['num']." ";
								//echo $inquery;
								//$flag = mysqli_query($link, $inquery) or die("Ошибка удаления!". mysqli_error($link));
							}
							echo"<b>Выбранный заказ удален.</b>";
							header('Refresh: 1, URL = orders.php');
						}?>
						<?php
                        /*

						foreach ($_SESSION['order'] as $key => $value){
							$inquery = "SELECT ticketsinorder.Amount, tickettype.Name, ticketsinorder.id_order FROM ticketsinorder INNER JOIN tickettype ON (ticketsinorder.id_ticket = tickettype.id_ticket) WHERE ticketsinorder.id_ticket = '".$value."'";
							$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
							//unset($_SESSION['id_order']);?>
                            <table border = 2><tr><td>Кол-во билетов</td><td>Билет</td><td>ID заказа</td></tr>
                            <?php
                            while ($result = mysqli_fetch_assoc($flag)){?>
                                <td><?php echo $result['Amount']?></td>
                                <td><?php echo $result['Name']?></td>
                                <td><?php echo $result['id_order']?></td>
                                </tr>
                            <?php
                                //$id_order = $result['id_order'];
                            }?>
                            </table>
                            <?php
                        }
						//unset($_SESSION['order']);
					*/?>
			</div></center>
        </div>
    </div>
</body>
<br><br><br><br><br>
<footer style="background: #990000">
		<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
</footer>
</html>