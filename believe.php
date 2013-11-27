<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('believe')) {
	dl('believe.' . PHP_SHLIB_SUFFIX);
}
$module = 'believe';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";
echo "\n";
var_dump(believe_error());
var_dump( believe_call("./be.so","say","qixiang"));
var_dump(believe_error());
var_dump( believe_call("./be2.so","say","qixiang"));
var_dump(believe_error());
?>
