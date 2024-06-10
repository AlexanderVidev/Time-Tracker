<?php
class User {
    public $id;
    public $username;
    public $password;
    public $role;
    public $userClass;
    public $hours;
    public $minutes;
    public $seconds;

    public function __construct($id, $username, $password, $role, $userClass, $hours, $minutes, $seconds) {
        $this->id = $id;
        $this->username = $username;
        $this->password = password_hash($password, PASSWORD_DEFAULT);
        $this->role = $role;
        $this->userClass = $userClass;
        $this->hours = $hours;
        $this->minutes = $minutes;
        $this->seconds = $seconds;
    }
}
?>
