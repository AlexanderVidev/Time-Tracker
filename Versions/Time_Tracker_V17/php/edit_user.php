<?php
include 'config.php';
include 'UserManager.php';

$userManager = new UserManager($conn);
$id = $_POST['id'];
$username = $_POST['username'];
$password = empty($_POST['password']) ? null : $_POST['password'];
$role = $_POST['role'];
$userClass = $_POST['userClass'];
$hours = intval($_POST['hours']);
$minutes = intval($_POST['minutes']);
$seconds = intval($_POST['seconds']);

if ($role === 'student' && empty(trim($userClass))) {
    echo "Failed to update user. Students must have a class.";
    exit();
}

if ($userManager->editUser($id, $username, $password, $role, $userClass)) {
    $userManager->updateUserTime($id, $hours, $minutes, $seconds);
    echo "User updated successfully.";
} else {
    echo "Failed to update user.";
}
?>