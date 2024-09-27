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
        // Calculate duration and update the end_time and duration in the same query
        $stmt = $this->conn->prepare("
            UPDATE time_logs 
            SET end_time = NOW(),
                duration_hours = TIMESTAMPDIFF(HOUR, start_time, NOW()),
                duration_minutes = MOD(TIMESTAMPDIFF(MINUTE, start_time, NOW()), 60),
                duration_seconds = MOD(TIMESTAMPDIFF(SECOND, start_time, NOW()), 60)
            WHERE user_id = ? 
              AND end_time IS NULL 
            ORDER BY start_time DESC 
            LIMIT 1");
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
