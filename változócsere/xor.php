<?php 
    $a = 25;
    $b = 12;

    echo 'a: ' . $a . '</br>';
    echo 'b: ' . $b . '</br>';

	$a = $a ^ $b;
	$b = $a ^ $b;
	$a = $a ^ $b; 
    
    echo 'a: ' . $a . '</br>';
    echo 'b: ' . $b . '</br>';

	$a = $a ^ $b;
	$b = $a ^ $b;
	$a = $a ^ $b; 
    
    echo 'a: ' . $a . '</br>';
    echo 'b: ' . $b . '</br>';

?>
