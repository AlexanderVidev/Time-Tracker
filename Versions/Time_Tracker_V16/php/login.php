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
        echo json_encode(['status' => 'success', 'redirect' => 'admin.html']);
    } else {
        echo json_encode(['status' => 'success', 'redirect' => 'user.html']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid login credentials']);
}
?>
