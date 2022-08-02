<!DOCTYPE html>
<html>
<?php
include "connect.php";
include "addition.php";
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
		<center><b style="font-family:Georgia;font-size: 15px;">Билеты</b></center><br>
		<center><div>
			<form metod="GET">
					<label for="filtr">Выберите необходимый фильтр: </label>
					<select name = "filtr">
								<option value="1" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '1') {
					echo 'selected';}?>>Без фильтра</option>
						<optgroup label="По типу">
								<option value="2" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '2') {
					echo 'selected';}?>>Одноразовый взрослый</option>
								<option value="3" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '3') {
					echo 'selected';}?>>Одноразовый детский</option>
								<option value="4" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '4') {
					echo 'selected';}?>>Абонемент</option>					
								<option value="5" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '5') {
					echo 'selected';}?>>Льготный</option>
						</optgroup>
						<optgroup label="По названию выставки">
								<option value="6" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '6') {
					echo 'selected';}?>>Арт-проект "Я понял"</option>
								<option value="7" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '7') {
					echo 'selected';}?>>Габриэл Викболд</option>
								<option value="8" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '8') {
					echo 'selected';}?>>Алексей Бегак. Другие берега</option>
								<option value="9" <?php if (!empty($_GET['filtr']) and $_GET['filtr'] === '9') {
					echo 'selected';}?>>Александр Кабин. Принадлежность</option>
						</optgroup>
					</select> 
					<br>
					<button name="sbm_filtr" type="submit">Применить фильтр</button>
				</form>
			</div></center>
		<center><div class="bd_tickets">
		<center><i>Внимание! При покупке льготного билета на входе необходимо предоставить подтвержающие документы!</i></center><br>
		<b>Выберите билет(ы), чтобы добавить в корзину</b><br>
		<?php
		if(isset($_GET['sbm_filtr'])){
			switch ($_GET['filtr']){
			case 1:
				$inquery = "SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img)";
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>

				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 2:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE tickettype.Name LIKE \'Одноразовый взрослый\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			
			case 3:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE tickettype.Name LIKE \'Одноразовый детский\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 4:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE tickettype.Name LIKE \'Абонемент\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 5:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE tickettype.Name LIKE \'Льготный\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 6:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE exhibition.exhibition_name LIKE \'Арт-проект "Я понял"\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 7:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE exhibition.exhibition_name LIKE \'Габриэл Викболд\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 8:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE exhibition.exhibition_name LIKE \'Алексей Бегак. Другие берега\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 8:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE exhibition.exhibition_name LIKE \'Алексей Бегак. Другие берега\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			case 9:
				$inquery = 'SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img) WHERE exhibition.exhibition_name LIKE \'Александр Кабин. Принадлежность\'';
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><th>Выберите...</th><th>Выставка</th><th>Цена билета</th><th>Тип</th></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"checkbox\" name=\"ticket[]\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
				<?php
                }?>
        		</table>
				<?php
				break;
			}
		}?>
		<button name="cart" type="submit">Добавить</button><br>
        </form>
		<?php
            if(isset($_GET['cart'])){
            	if(!empty($_GET['ticket'])){
                    if(isset($_SESSION['user'])){
						$_SESSION['order'] = $_GET['ticket'];
						foreach ($_SESSION['order'] as $key => $value){
							//echo $_SESSION['order'];
							//echo $value;
							$inquery = "INSERT INTO  cart (id_cart, id_user,id_ticket) VALUES (NULL,'".$_SESSION['user']['id']."','".$value."')";
							$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
						}
						//$inquery = "INSERT INTO  cart (id_cart, id_user,id_ticket) VALUES (NULL,'".$_SESSION['user']['id']."','".$_GET['ticket']."')";
						//$flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));

						echo "<b>Билет(ы) добавлен(ы) в вашу корзину. Корзину можно посмотреть в <a href=\"personal.php\">личном кабинете</a>.";
						//unset($_SESSION['order']);
					}
					else{
						echo "<b>Билет не может быть добавлен! Вам необходимо пройти <a href=\"auth.php\">авторизацию</a> либо <a href=\"registr.php\">зарегистрироваться</a>!";
					}
                }
			}?>
		</div></center>
<br><br>
	<footer style="background: #990000">
		<center>Elizaveta Mikheenko erarta.museum.com ©2022</center>
	</footer>

</body>

</html>
