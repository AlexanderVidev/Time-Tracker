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

    public function getUserById($id) {
        $stmt = $this->conn->prepare("SELECT * FROM users WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();
        return $stmt->get_result()->fetch_assoc();
    }

    public function getAllUsers() {
        $stmt = $this->conn->prepare("SELECT * FROM users");
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    public function deleteUser($id) {
        $stmt = $this->conn->prepare("DELETE FROM users WHERE id = ?");
        $stmt->bind_param("i", $id);
        return $stmt->execute();
    }

    public function editUser($id, $username, $password, $role, $userClass) {
        if ($password === null) {
            $stmt = $this->conn->prepare("UPDATE users SET username = ?, role = ?, userClass = ? WHERE id = ?");
            $stmt->bind_param("sssi", $username, $role, $userClass, $id);
        } else {
            $hashed_password = password_hash($password, PASSWORD_DEFAULT);
            $stmt = $this->conn->prepare("UPDATE users SET username = ?, password = ?, role = ?, userClass = ? WHERE id = ?");
            $stmt->bind_param("ssssi", $username, $hashed_password, $role, $userClass, $id);
        }
        return $stmt->execute();
    }

    public function updateUserTime($id, $hours, $minutes, $seconds) {
        $stmt = $this->conn->prepare("UPDATE users SET hours = ?, minutes = ?, seconds = ? WHERE id = ?");
        $stmt->bind_param("iiii", $hours, $minutes, $seconds, $id);
        return $stmt->execute();
    }

    public function userExists($username) {
        $stmt = $this->conn->prepare("SELECT * FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $result = $stmt->get_result();
        return $result->num_rows > 0;
    }
    
}
?>