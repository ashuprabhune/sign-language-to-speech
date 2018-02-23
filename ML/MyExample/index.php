
<html>
<body>
<form method="get">
<input type="submit" class="button" name="start" value="start_training" />
<input type="submit" class="button" name="Record" value="Record" />
<input type="submit" class="button" name="getop" value="getop" />
<input type="submit" class="button" name="load" value="load" />
<input type="submit" class="button" name="nextg" value="nextgesture" />
<input type="submit" class="button" name="save" value="saveDataset" />
</form>
<?php
function sendr(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "t" ;
echo "Message To server :".$message;
// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//echo "Reply From Server  :".$result;
// close socket
socket_close($socket);
}
//if(array_key_exists('start',$_POST)){
//   start();
//}
if($_GET){
    if(isset($_GET['start'])){
        sendr();

    }elseif(isset($_GET['load'])){
        load();
	
    }elseif(isset($_GET['Record'])){
        record();
	
    }elseif(isset($_GET['getop'])){
        getop();
	
    }elseif(isset($_GET['nextg'])){
        nextg();
	
    }elseif(isset($_GET['save'])){
        save();
	
    }
}
function record(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "r" ;
echo "Message To server :".$message;
// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//echo "Reply From Server  :".$result;
// close socket
socket_close($socket);
}
function save(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "s" ;
echo "Message To server :".$message;
// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//echo "Reply From Server  :".$result;
// close socket
socket_close($socket);
}
//if(array_key_exists('start',$_POST)){
//   start();
//}
function load(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "l" ;
echo "Message To server :".$message;
// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//echo "Reply From Server  :".$result;
// close socket
socket_close($socket);
}
function nextg(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "[" ;
echo "Message To server :".$message;
// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//echo "Reply From Server  :".$result;
// close socket
socket_close($socket);
}
function getop(){
$host    = "127.0.0.1";
$port    = 2000;
$message = "p" ;

// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server

//socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
if($result) { 
// get server response

$result = socket_read ($socket, 1024) or die("Could not read server response\n");
}

echo "Reply From Server  :".$result ."<br>";

// close socket
//socket_close($socket);
$url1=$_SERVER['REQUEST_URI'];
header("Refresh: 1; URL=$url1");
}

function start(){
$message ="r";
echo $message;

$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  
// send string to server
// connect to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
}

function stop(){
$message ="r";
echo $message;
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
}
?>

</body>
</html>
