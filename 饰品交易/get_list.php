<?php
include "connect.php";
$start_position=$_POST['start_position'];
$counter_a=0;
$counter_b=0;

$list="select*from commodity";
$r0=mysqli_query($conn,$list);

echo "<table class='list_table' id='list_table'>
			<tr>
				<th>commodity ID</th>
				<th>skin name</th>
				<th>status</th>
			</tr>";

while($l=mysqli_fetch_array($r0)){
	if($counter_a<$start_position){
		$counter_a++;
		continue;
	}
	if($counter_b>=50) break;
	echo "
		<tr>
			<td>$l[0]</td>
			<td>$l[1]</td>
			<td>$l[8]</td>
		</tr>	
	";
	$counter_b++;
}

echo "</table>";

?>