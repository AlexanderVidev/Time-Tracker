<?php
include 'config.php';
include 'UserManager.php';

$userManager = new UserManager($conn);
$id = $_POST['id'];

if ($userManager->deleteUser($id)) {
    echo json_encode(["status" => "success", "message" => "User deleted successfully"]);
} else {
    echo json_encode(["status" => "error", "message" => "Failed to delete user"]);
}
?>
