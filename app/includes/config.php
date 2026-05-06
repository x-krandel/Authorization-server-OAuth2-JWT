<?php


function config($key='')
{
    $config = [
        'name' => "Simple PHP Website",
        'simple_url' => '',
        'pretty_uri' => false,
        'nav_menu' => [
            '' => 'Home',
            'about-us' => 'About Us',
            'products' => 'Products',
            'contact' => 'Contact',
            'login' => 'Login',
        ],
        'template_path' => 'template',
        'content_path' => 'content',
        'version' => 'v3.1',
    ];
    return isset($config[$key]) ? $config[$key] : null;
} 


