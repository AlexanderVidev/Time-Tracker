<?php
include 'config.php';
include 'UserManager.php';

$userManager = new UserManager($conn);
$username = $_POST['username'];
$password = $_POST['password'];
$role = $_POST['role'];
$userClass = $_POST['userClass'];

if (!preg_match('/^[a-zA-Z0-9_]{3,20}$/', $username)) {
    echo json_encode(["status" => "error", "message" => "Invalid username. Use 3-20 alphanumeric characters or underscores."]);
    exit();
}

if (strlen($password) < 5) {
    echo json_encode(["status" => "error", "message" => "Password must be at least 5 characters long."]);
    exit();
}

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
