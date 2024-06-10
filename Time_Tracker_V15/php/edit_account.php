<?php
session_start();
include 'config.php';
include 'UserManager.php';

if (!isset($_SESSION['user_id'])) {
    echo "User not logged in.";
    exit();
}

$user_id = $_SESSION['user_id'];
$newUsername = $_POST['username'];
$newPassword = $_POST['password'];
$newClass = $_POST['class'];

$userManager = new UserManager($conn);
$user = $userManager->getUserById($user_id);

if ($user) {
    // Update user details
    $newUsername = empty($newUsername) ? $user['username'] : $newUsername;
    $newPassword = empty($newPassword) ? null : $newPassword;
    $newClass = empty($newClass) ? $user['userClass'] : $newClass;

    if ($userManager->editUser($user_id, $newUsername, $newPassword, $user['role'], $newClass)) {
        echo "Account updated successfully.";
    } else {
        echo "Failed to update account.";
    }
} else {
    echo "User not found.";
}
?>