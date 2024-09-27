<?php
session_start();
include 'UserManager.php';

if (!isset($_SESSION['user_id']) || $_SESSION['role'] !== 'instructor') {
    header("Location: ../index.html");
    exit();
}

$userManager = new UserManager($conn);
$users = $userManager->getAllUsers();

function displayUsers($users) {
    foreach ($users as $user) {
        echo "<tr>";
        echo "<td>{$user['username']}</td>";
        echo "<td>{$user['role']}</td>";
        echo "<td>{$user['userClass']}</td>";
        echo "<td>{$user['hours']}h {$user['minutes']}m {$user['seconds']}s</td>";
        echo "<td><button onclick=\"editUser('{$user['id']}')\">Edit</button></td>";
        echo "<td><button onclick=\"deleteUser('{$user['id']}')\">Delete</button></td>";
        echo "</tr>";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Interface</title>
    <link rel="stylesheet" href="../css/styles.css">
</head>
<body>
    <h1>Admin Interface</h1>
    <h2>Manage Users</h2>
    <table>
        <thead>
            <tr>
                <th>Username</th>
                <th>Role</th>
                <th>Class</th>
                <th>Logged Time</th>
                <th>Edit</th>
                <th>Delete</th>
            </tr>
        </thead>
        <tbody>
            <?php displayUsers($users); ?>
        </tbody>
    </table>
    <a href="logout.php">Logout</a>
</body>
</html>
