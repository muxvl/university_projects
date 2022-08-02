<?php 

function clear($string){//функция для удаления лишних элементов из строчек
    $string = trim($string);   // для удаления пробелов из начала и конца строки
    $string = stripslashes($string);  // для удаления экранированных символов 
    $string = strip_tags($string);  //  нужна для удаления HTML и PHP тегов
    $string = htmlspecialchars($string);   // преобразует специальные символы в HTML-сущности ('&' преобразуется в '&amp;' и т.д.)
    return $string;
}

function checkSize($string,$min,$max){//проверка длины строки
    $result = (mb_strlen($string) > $min && mb_strlen($string) <= $max);
    return $result;
}

function printTable($res){
    include "connect.php";
    if($res){
        while ($r = mysqli_fetch_assoc($res)){
        //echo $res['image'];
        echo "<table>
                    <tr>
                    <td>
                        <center><img src = \"".$r['image']."\" width=\"280\" height=\"180\"></center>
                    </td>
                    <td>
                        <b>Название: ".$r['name']."</b><br>
                        Тип: ".$r['name_type']."</center><br>
                        Объем аквариума ".$r['size']." литров Вода ".$r['name_aqua']."

                    </td></tr>

                    </table>";
                }

}
}

function printTicket($res){
    include "connect.php";?>
    <form metod=GET>
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
    <b>Выберите билет, чтобы добавить в корзину</b><br>
    <input type="submit" name="cart" value="Добавить">
    </form>
    <?php
    if(isset($_GET['cart'])){
        if(!empty($_GET['ticket'])){
                if(isset($_SESSION['user'])){
                    $_SESSION['m'] = $_GET['ticket'];
                    echo $_SESSION['m'];
                    $inquery = "INSERT INTO  cart (id_cart, id_user,id_ticket) VALUES (NULL,'".$_SESSION['user']['id']."','".$_GET['ticket']."')";
                    $flag = mysqli_query($link, $inquery) or die("Ошибка добавления!". mysqli_error($link));
                    echo "<b>Билет добавлен в вашу корзину. Корзину можно посмотреть и изменить в <a href=\"personal.php\">личном кабинете</a>.";
                }
                else{
                    echo "<b>Билет не может быть добавлен! Вам необходимо пройти <a href=\"auth.php\">авторизацию</a> либо <a href=\"registr.php\">зарегистрироваться</a>!";
                }
            }
        }

}

?>



