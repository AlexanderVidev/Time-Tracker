<?php
session_start();
include 'config.php';
include 'TimeTracker.php';

if (!isset($_SESSION['user_id'])) {
    echo "User not logged in.";
    exit();
}

$user_id = $_SESSION['user_id'];
$timeTracker = new TimeTracker($conn);

if ($timeTracker->stop($user_id)) {
    echo "Timer stopped successfully.";
} else {
    echo "Failed to stop timer.";
}
?>
