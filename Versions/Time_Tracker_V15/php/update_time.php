<?php
session_start();
include 'config.php';
include 'UserManager.php';

if (!isset($_SESSION['user_id'])) {
    echo "User not logged in.";
    exit();
}

$user_id = $_SESSION['user_id'];
$hours = intval($_POST['hours']);
$minutes = intval($_POST['minutes']);
$seconds = intval($_POST['seconds']);

$userManager = new UserManager($conn);
$user = $userManager->getUserById($user_id);

if ($user) {
    // Update user's logged time in the database
    $new_hours = $hours;
    $new_minutes = $minutes;
    $new_seconds = $seconds;

    // Normalize time
    $new_minutes += intdiv($new_seconds, 60);
    $new_seconds %= 60;
    $new_hours += intdiv($new_minutes, 60);
    $new_minutes %= 60;

    if ($userManager->updateUserTime($user_id, $new_hours, $new_minutes, $new_seconds)) {
        echo "Time updated successfully.";
    } else {
        echo "Failed to update time.";
    }
} else {
    echo "User not found.";
}
?>
