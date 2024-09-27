<?php
session_start();
include 'UserManager.php';

if (!isset($_SESSION['user_id']) || $_SESSION['role'] !== 'instructor') {
    header("Location: ../index.html");
    exit();
}

$userManager = new UserManager($conn);
$users = $userManager->getAllUsers();

echo json_encode($users);
?>
