<?php
    session_start();
    include "connect.php";
    $FIO = $_POST['FIO'];
    $login = $_POST['login'];
    $email = $_POST['email'];
    $pwd = $_POST['pwd'];
    $pwd_confirm = $_POST['pwd_confirm'];

    $inquery = "SELECT * FROM user WHERE login = '".$login."'";
    $flag = mysqli_query($link, $inquery) or die("Ошибка!". mysqli_error($link));
    $result = mysqli_fetch_assoc($flag);
    if($result == 0){
        if($pwd === $pwd_confirm){
        $pwd = md5($pwd);
        mysqli_query($link, "INSERT INTO `user` (`id_user`, `FIO`, `login`, `pwd`, `email`) VALUES (NULL, '$FIO', '$login', '$pwd', '$email')");
        $_SESSION['msg'] = 'Регистрация прошла успешно.';
        header('Location: /auth.php');
        }
         else{
        $_SESSION['msg'] = 'Пароли не совпадают!';
        header('Location: /registr.php');
        }
    }
    else{
        $_SESSION['msg'] = 'Пользователь с таким логином существует!';
        header('Location: /registr.php');
    }
?>

