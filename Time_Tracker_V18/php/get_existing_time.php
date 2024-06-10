<?php
session_start();
include 'config.php';
include 'UserManager.php';

if (!isset($_SESSION['user_id'])) {
    echo json_encode(['hours' => 0, 'minutes' => 0, 'seconds' => 0]);
    exit();
}

$user_id = $_SESSION['user_id'];
$userManager = new UserManager($conn);
$user = $userManager->getUserById($user_id);

if ($user) {
    echo json_encode([
        'hours' => $user['hours'],
        'minutes' => $user['minutes'],
        'seconds' => $user['seconds']
    ]);
} else {
    echo json_encode(['hours' => 0, 'minutes' => 0, 'seconds' => 0]);
}
?>
