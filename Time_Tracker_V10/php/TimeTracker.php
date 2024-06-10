<?php
include 'config.php';

class TimeTracker {
    private $conn;

    public function __construct($conn) {
        $this->conn = $conn;
    }

    public function start($user_id) {
        $stmt = $this->conn->prepare("INSERT INTO time_logs (user_id, start_time) VALUES (?, NOW())");
        $stmt->bind_param("i", $user_id);
        return $stmt->execute();
    }

    public function stop($user_id) {
        $stmt = $this->conn->prepare("UPDATE time_logs SET end_time = NOW() WHERE user_id = ? AND end_time IS NULL");
        $stmt->bind_param("i", $user_id);
        return $stmt->execute();
    }

    public function getTimeLogs($user_id) {
        $stmt = $this->conn->prepare("SELECT * FROM time_logs WHERE user_id = ?");
        $stmt->bind_param("i", $user_id);
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }
}
?>