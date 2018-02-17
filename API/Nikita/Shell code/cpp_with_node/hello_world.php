
<!DOCTYPE html>
<html>
<body>

<h1>My first PHP page</h1>

<?php
 ob_start()
$result = shell_exec('C:/Users/nikita_shah/Desktop/cpp_with_node/add_user.sh');
echo $result;
ob_end_clean(); 
?>

</body>
</html>