<?php
include 'config.php';
include 'UserManager.php';

$userManager = new UserManager($conn);
$user_id = $_POST['id'];

$user = $userManager->getUserById($user_id);
echo json_encode($user);
?>
