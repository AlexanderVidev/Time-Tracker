<?php
include 'config.php';
include 'TimeTracker.php';

$user_id = $_POST['user_id'];
$timeTracker = new TimeTracker($conn);
$logs = $timeTracker->getTimeLogs($user_id);

echo json_encode($logs);
?>
