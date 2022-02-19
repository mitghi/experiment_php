<?php 

	if (!extension_loaded('counter')) {
		echo '[-] counter extension not loaded\n';
		return;		
	}

	echo "[*] Loading file ....\n";
	$f = file_get_contents("/tmp/big.txt"); // 17.6 Gb file
	$len = strlen($f) / 1000000000;
	echo "[+] File loaded ( Filesize: $len Gb )\n";

	/* C-Extension section */
	
	$starttime = microtime(true);
	$cnt = counter_count_commas($f);		
	$endtime = microtime(true);
	$timediff = $endtime - $starttime;
	
	echo "[+] C_EXTENSION took: $timediff seconds, commas count: $cnt\n";
	
	/* end section */


	/* naive section */
	
	$starttime = microtime(true);
	$cnt = 0;
	for ($i = 0; $i < strlen($f); $i++) {
	    if ($f[$i] == ",") $cnt += 1;	    
	}

	$endtime = microtime(true);
	$timediff = $endtime - $starttime;
	
	echo "[+] PHP_Normal took: $timediff seconds, commas count: $cnt\n";

	/* end section */
?>
