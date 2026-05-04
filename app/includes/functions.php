<?php



function site_name()
{
    echo config('name');
}

function site_url()
{
    echo config('site_url');
}

function site_version()
{
    echo config('version');
}

function nav_menu($sep = ' | ')
{
    $nav_menu='';
    $nav_items=config('nav_menu');

    foreach ($nav_items as $uri => $name) {
        $query_string = str_replace('page=', '', $_SERVER['QUERY_STRING'] ?? '');
        $class = $query_string == $uri ? ' active' : '';
        $url = config('site_url') . '/' . ( config('pretty_uri') || $uri == '' ? '' : '?page=') . $uri;

        $nav_menu .= '<a href="' . $url . '" title="' . $name . '" class="item ' . $class . '">' . $name . '</a>' . $sep;

        }
        echo trim($nav_menu, $sep); // rekursja ?

}

function page_title()
{
    $page = isset($_GET['page']) ? htmlspecialchars($_GET['page']) : 'Home';

    echo ucwords(str_replace('-', ' ', $page));
}


function page_content()
{
    $page = isset($_GET['page']) ? $_GET['page'] : 'Home';
    $path = getcwd() . '/' . config('content_path') . '/404.phtml'; 

    if (! file_exists($path)) {
        $path = getcwd() . '/' . config('content_path') . '/404.phtml';
    }

    echo file_get_contents($path);
}


function init() {
    require config('template_path') . '/template.php';
}

?>