<?php
session_start();
include 'UserManager.php';

$userManager = new UserManager($conn);
$username = $_POST['username'];
$password = $_POST['password'];
$role = $_POST['role'];

$user = $userManager->authenticate($username, $password);

if ($user && $user['role'] === $role) {
    $_SESSION['user_id'] = $user['id'];
    $_SESSION['role'] = $user['role'];
    if ($role === 'instructor') {
        header("Location: ../admin.html");
    } else {
        header("Location: ../user.html");
    }
} else {
    echo "Invalid login credentials";
}
?>
