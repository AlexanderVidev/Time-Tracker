<?php
include 'config.php';
include 'UserManager.php';

$userManager = new UserManager($conn);
$username = $_POST['username'];
$password = $_POST['password'];
$role = $_POST['role'];
$userClass = $_POST['userClass'];

// Check if the username already exists
if ($userManager->userExists($username)) {
    echo json_encode(["status" => "error", "message" => "Account already exists"]);
} else {
    if ($userManager->createUser($username, $password, $role, $userClass)) {
        echo json_encode(["status" => "success", "message" => "User registered successfully"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Failed to register user"]);
    }
}
?>