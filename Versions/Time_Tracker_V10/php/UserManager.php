<?php
include 'config.php';
include 'User.php';

class UserManager {
    private $conn;

    public function __construct($conn) {
        $this->conn = $conn;
    }

    public function createUser($username, $password, $role, $userClass = "") {
        $stmt = $this->conn->prepare("INSERT INTO users (username, password, role, userClass) VALUES (?, ?, ?, ?)");
        $hashed_password = password_hash($password, PASSWORD_DEFAULT);
        $stmt->bind_param("ssss", $username, $hashed_password, $role, $userClass);
        return $stmt->execute();
    }

    public function authenticate($username, $password) {
        $stmt = $this->conn->prepare("SELECT * FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $result = $stmt->get_result();
        $user = $result->fetch_assoc();

        if ($user && password_verify($password, $user['password'])) {
            return $user;
        }
        return null;
    }
    
    public function getAllUsers() {
    $stmt = $this->conn->prepare("SELECT * FROM users");
    $stmt->execute();
    return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }


    // Additional methods for user management (view, edit, delete) can be added here
}
?>
