<?php 
$date = date("d.m.y");
$ip = $_SERVER["REMOTE_ADDR"];
$file1 = "ip".$str.".txt";
$file2 = "count".$str.".txt";

if(!file_exists($file2)){
    $all = 1;
    $today = 1;
    $ip_num = 1;
    $count = $all."\n".$date."\n".$today;

    $check = fopen($file2, "w+");
    fwrite($check, $count);
    fclose($check);

    $ip2 = fopen($file1, "w+");
    fwrite($ip2, $ip."\n");
    fclose($ip2);
}
else{
    $file = file($file2);
    foreach($file as $str){
        $mass[] = $str;
    }

    $all = (int)$mass[0];
    $date2 = (float)$mass[1];
    $today = (int)$mass[2];
    $all++;

    if($date2 != $date){
        $today = 1;
    }
    else{
        $today++;
    }

    $count2 = $all."\n".$date."\n".$today;

    $check = fopen($file2, "w+");
    flock($check, LOCK_EX);
    fwrite($check, $count2);
    flock($check, LOCK_UN);
    fclose($check);

    $ip2 = file($file1);
    $ip_num = count($ip2);

    if(in_array($ip."\n", $ip2) == false){
        $ipopen = fopen($file1, "a");
        flock($ipopen, LOCK_EX);
        fwrite($ipopen, $ip."\n");
        flock($ipopen, LOCK_UN);
        $ip_num++;
        fclose($ipopen);
    }
}
?>

<html>
    <center><table border = 2 borderColor = #990000>
        <tr><td colspan="2">Посещаемость сайта за <?php echo $date ?></td><tr>
        <tr><th>Всего:</th><th>Сегодня:</th></tr>
        <tr><th><?php echo $all?></th><th><?php echo $today?></th></tr>
        <tr><th><?php echo $all?></th><th><?php echo $today?></th></tr>
        <tr><td colspan="2">Посетителей с разным IP: <?php echo $ip_num ?></td><tr>
    </table></center>
</html>