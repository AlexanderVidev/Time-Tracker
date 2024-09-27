let startTime;
let timerInterval;
let updateInterval;
let existingHours = 0;
let existingMinutes = 0;
let existingSeconds = 0;
let isTimerRunning = false;

function startTimer() {
    if (isTimerRunning) {
        alert("Error: Timer is already running.");
        return;
    }

    // Fetch existing time from the server
    fetch('php/get_existing_time.php')
        .then(response => response.json())
        .then(data => {
            existingHours = data.hours;
            existingMinutes = data.minutes;
            existingSeconds = data.seconds;

            startTime = new Date();
            timerInterval = setInterval(updateTime, 1000);
            updateInterval = setInterval(updateServerTime, 1000);  // Update server every 1 second
            isTimerRunning = true;

            // Initialize the display with the current logged time
            updateDisplayedTime(existingHours, existingMinutes, existingSeconds);
        });
}

function stopTimer() {
    if (!isTimerRunning) {
        alert("Error: Timer is not running.");
        return;
    }

    clearInterval(timerInterval);
    clearInterval(updateInterval);
    const endTime = new Date();
    const elapsed = Math.floor((endTime - startTime) / 1000);
    const hours = Math.floor(elapsed / 3600);
    const minutes = Math.floor((elapsed % 3600) / 60);
    const seconds = elapsed % 60;

    // Update the display with the final logged time
    updateDisplayedTime(existingHours + hours, existingMinutes + minutes, existingSeconds + seconds);

    // Send final time update to the server
    updateServerTime(hours, minutes, seconds);
    isTimerRunning = false;
}

function updateTime() {
    const currentTime = new Date();
    const elapsed = Math.floor((currentTime - startTime) / 1000);
    const hours = Math.floor(elapsed / 3600);
    const minutes = Math.floor((elapsed % 3600) / 60);
    const seconds = elapsed % 60;

    updateDisplayedTime(existingHours + hours, existingMinutes + minutes, existingSeconds + seconds);
}

function updateDisplayedTime(hours, minutes, seconds) {
    const totalSeconds = seconds;
    const totalMinutes = minutes + Math.floor(totalSeconds / 60);
    const displaySeconds = totalSeconds % 60;
    const displayHours = hours + Math.floor(totalMinutes / 60);
    const displayMinutes = totalMinutes % 60;

    document.getElementById('loggedTime').innerText = `Logged Time: ${displayHours}h ${displayMinutes}m ${displaySeconds}s`;
}

function updateServerTime(hours, minutes, seconds) {
    const currentTime = new Date();
    const elapsed = Math.floor((currentTime - startTime) / 1000);

    if (hours === undefined || minutes === undefined || seconds === undefined) {
        hours = Math.floor(elapsed / 3600);
        minutes = Math.floor((elapsed % 3600) / 60);
        seconds = elapsed % 60;
    }

    const totalSeconds = existingSeconds + seconds;
    const totalMinutes = existingMinutes + minutes + Math.floor(totalSeconds / 60);
    const newSeconds = totalSeconds % 60;
    const newHours = existingHours + hours + Math.floor(totalMinutes / 60);
    const newMinutes = totalMinutes % 60;

    // Send AJAX request to update logged time
    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/update_time.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            console.log(xhr.responseText);
        }
    };
    xhr.send(`hours=${newHours}&minutes=${newMinutes}&seconds=${newSeconds}`);
}

function showEditAccount() {
    document.getElementById('editAccountForm').style.display = 'block';
}

function hideEditAccount() {
    document.getElementById('editAccountForm').style.display = 'none';
    document.getElementById('editAccount').reset();  // Clear the form fields
}

function editAccount() {
    const newUsername = document.getElementById('newUsername').value;
    const newPassword = document.getElementById('newPassword').value;
    const newClass = document.getElementById('newClass').value;

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/edit_account.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            alert(xhr.responseText);
            if (xhr.responseText.includes("successfully")) {
                hideEditAccount();
            }
        }
    };
    xhr.send(`username=${newUsername}&password=${newPassword}&class=${newClass}`);
}

// Function to fetch and display users in the admin page
function fetchUsers() {
    fetch('php/admin.php')
        .then(response => response.json())
        .then(users => {
            const userTableBody = document.getElementById('userTableBody');
            userTableBody.innerHTML = '';
            users.forEach(user => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${user.username}</td>
                    <td>${user.role}</td>
                    <td>${user.userClass}</td>
                    <td>${user.hours}h ${user.minutes}m ${user.seconds}s</td>
                    <td><button onclick="editUser(${user.id})">Edit</button></td>
                    <td><button onclick="deleteUser(${user.id})">Delete</button></td>
                `;
                userTableBody.appendChild(row);
            });
        });
}

document.addEventListener('DOMContentLoaded', fetchUsers);