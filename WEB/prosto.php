<?php 
while($result = mysqli_fetch_assoc($flag)){
					?>
					<table>
					<tr>
					<td>
						<center><img src="img/<?php echo $result['image']?>.jpeg" width="550" height="380"></center>
					</td>
					<td>
						<b>Выставка:<?php echo $result['exhibition_name']?></b><br>
						Тип: <?php echo $result['Name']?><br>
						Цена: <?php echo $result['ticket_price']?> 
					</td>
					</tr>
					</table>
				<?php
				}?>

				<b>Выберите билет, чтобы добавить в корзину</b><br>
                <input type="submit" name="ok" value="Добавить">
                <?php

                if(isset($_GET['ok'])){
                    if(!empty($_GET['ticket'])){
                            if(isset($_SESSION['id'])){
                            $quer = "INSERT INTO basket (id_user,id_ticket,dateZ,stat) VALUES ('".$_SESSION['id']."','".$_GET['ticket']."','".date('y.m.d', strtotime('today'))."',0)";
                            $quer = mysqli_query($conn, $quer) or die("Ошибка добавления данных" . mysqli_error($conn));
                            echo "Добавлено";
                        }
                        else{
                            echo "К сожалению вы не зарегистрированы<b> <a href=\"autor.php\">Авторизуйтесь</a> или <a href=\"reg.php\">зарегистрируйтесь</a> на сайте и возвращайтесь";
                        }
                    }
                    else{
                        echo "<b>Ничего не выбрано :(</b>";
                    }
				}?>

<?php //печать таблицы с билетами ?>
<?php
$inquery = "SELECT ticket.id_ticket, ticket.ticket_price, exhibition.exhibition_name, tickettype.Name, images.image FROM exhibition INNER JOIN ticket ON (exhibition.id_exhibition = ticket.id_exhibition) INNER JOIN tickettype ON (ticket.id_type = tickettype.id_type) INNER JOIN images ON (exhibition.id_img = images.id_img)";
				$flag = mysqli_query($link, $inquery) or die("Ошибка запроса". mysqli_error($conn));
				?>
				<form metod = GET>
        		<table border = 2><tr><td>Выберите...</td><td>Выставка</td><td>Цена билета</td><td>Тип</td></tr>
        		<?php
				while ($result = mysqli_fetch_assoc($flag)){
					echo "<td><input type=\"radio\" name=\"ticket\" value=\"".$result['id_ticket']."\"></td>"?>
					<td><?php echo $result['exhibition_name']?></td>
                    <td><?php echo $result['ticket_price']?></td>
                    <td><?php echo $result['Name']?></td>
                    </tr>
			
				<?php
                }?>
        		</table>
<pre>
	<?php
    print_r($_SESSION);
    ?>
</pre>