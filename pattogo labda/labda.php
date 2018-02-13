<?php

function gotoxy($x, $y) {
    for($i=0; $i < $y; $i++) {
      echo"\n";
    }

    for($i=0; $i < $x; $i++) {
      echo" ";
    }

    echo"o\n";
}

$egyx = 1;
$egyy = -1;
$x = 10;
$y = 20;
$ty = array();
$tx = array();

for($i = 0; $i < 23; $i++) {
  array_push($ty, 1);
}

$replacety = array(1 => -1, 22 => -1);
$ty = array_replace($ty, $replacety);


for($i = 0; $i < 80; $i++) {
  array_push($tx, 1);
}

$replacetx = array(1 => -1, 79 => -1);
$tx = array_replace($tx, $replacetx);


for(;;) {

  for($i=0; $i < 37; $i++) {
    echo"_";
  }

  echo "x=",$x,"y=",$y;

  for($i=0; $i < 37; $i++) {
    echo"_";
  }

  gotoxy($x, $y);

  $x += $egyx;
  $y += $egyy;

  $egyx *= $tx[$x];
  $egyy *= $ty[$y];

  sleep(1);
  system('clear');

}

?>
