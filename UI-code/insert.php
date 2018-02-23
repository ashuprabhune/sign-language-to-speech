

    <?php

    /* Attempt MySQL server connection. Assuming you are running MySQL

    server with default setting (user 'root' with no password) */

    $link = mysqli_connect("localhost", "root", "root", "textDb");

     

    // Check connection

    if($link === false){

        die("ERROR: Could not connect. " . mysqli_connect_error());

    }

     

    // Escape user inputs for security

    $input_label = strtolower($_POST[text]);     
    // attempt insert query execution
    
    $arr = array();
    $sql1 = "SELECT * FROM textTable WHERE text_label='$input_label'";
    $query = mysqli_query($link,$sql1);
	if(mysqli_num_rows($query) == 0){
		
	$sql = "INSERT INTO textTable (text_label) VALUES ('$input_label')";
   
	    if(mysqli_query($link, $sql)){
		
		$last_id = $link->insert_id;
		$arr['data1'] = $last_id;
		$suc = "Records added successfully." . $last_id;

	    } else{

		echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);

	    }
	}

	else{
		$present =  "Record already present!!";
		$aa['data2'] = $present;
		
	}

     
	echo json_encode($arr);
    // close connection

    mysqli_close($link);

    ?>


