<?php
session_start();
include 'config.php';
include 'UserManager.php';
include 'TimeTracker.php';

if (!isset($_SESSION['user_id'])) {
    echo json_encode(['status' => 'error', 'message' => 'User not logged in.']);
    exit();
}

$user_id = $_SESSION['user_id'];
$hours = intval($_POST['hours']);
$minutes = intval($_POST['minutes']);
$seconds = intval($_POST['seconds']);
$isFinalUpdate = isset($_POST['isFinalUpdate']) ? $_POST['isFinalUpdate'] === 'true' : false;

$userManager = new UserManager($conn);
$timeTracker = new TimeTracker($conn);
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
        if ($isFinalUpdate) {
            $timeTracker->stop($user_id);
        }
        echo json_encode([
            'status' => 'success',
            'hours' => $new_hours,
            'minutes' => $new_minutes,
            'seconds' => $new_seconds,
            'message' => 'Time updated successfully.'
        ]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Failed to update time.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'User not found.']);
}
?>
