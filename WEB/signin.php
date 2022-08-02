<?php
    session_start();
    include "connect.php";
    $login = $_POST['login'];
    $pwd = md5($_POST['pwd']);

    $check = mysqli_query($link,"SELECT * FROM `user` WHERE `login` = '$login' AND `pwd` = '$pwd'");
    if (mysqli_num_rows($check) > 0){
        $user = mysqli_fetch_assoc($check);

        $_SESSION['user'] = [
            "id"=>$user['id_user'],
            "FIO"=>$user['FIO'],
            "login"=>$user['login'],
            "email"=>$user['email'],
            "pwd"=>$user['pwd']
        ];

        header('Location: /personal.php');
    }
    else{
        $_SESSION['msg'] = 'Неверный логин или пароль!';?>
        <a href="auth.php">Авторизация</a>
        <?php
        //header('Location: /auth.php');
    }

?>
<pre>
    <?php
    print_r($check);
    print_r($user);
    ?>
</pre>