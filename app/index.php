<?php



error_reporting(E_ALL);
ini_set('display_errors', 1);

require 'includes/functions.php';
require 'includes/config.php';

$page = isset($_GET['page']) ? basename($_GET['page']) : 'home';

$actions = ['login_process'];

if (in_array($page, $actions)) {
    $path = getcwd() . '/' . config('content_path') . '/' . $page . '.phtml';
    if (file_exists($path)){
        include $path;
        exit();
    }
}

init();


