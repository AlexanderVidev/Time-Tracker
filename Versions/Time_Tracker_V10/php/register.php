<?php
include 'UserManager.php';

$userManager = new UserManager($conn);
$username = $_POST['username'];
$password = $_POST['password'];
$role = $_POST['role'];
$userClass = $_POST['userClass'];

if ($userManager->createUser($username, $password, $role, $userClass)) {
    echo "User registered successfully";
} else {
    echo "Failed to register user";
}
?>
