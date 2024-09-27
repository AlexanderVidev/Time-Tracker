<?php
session_start();
include 'config.php';
include 'TimeTracker.php';

if (!isset($_SESSION['user_id'])) {
    echo json_encode(['status' => 'error', 'message' => 'User not logged in.']);
    exit();
}

$user_id = $_SESSION['user_id'];
$timeTracker = new TimeTracker($conn);

if ($timeTracker->stop($user_id)) {
    echo json_encode(['status' => 'success', 'message' => 'Timer stopped successfully.']);
} else {
    echo json_encode(['status' => 'error', 'message' => 'Failed to stop timer.']);
}
?>
