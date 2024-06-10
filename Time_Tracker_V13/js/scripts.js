let startTime;
let timerInterval;
let updateInterval;
let existingHours = 0;
let existingMinutes = 0;
let existingSeconds = 0;
let isTimerRunning = false;
let editUserId;

function displayMessage(message, isSuccess) {
    const messageElement = document.getElementById('message');
    messageElement.innerText = message;
    messageElement.style.color = isSuccess ? 'green' : 'red';
    messageElement.style.display = 'block';
    setTimeout(() => {
        messageElement.style.display = 'none';
    }, 5000);  // Clear the message after 5 seconds
}

function startTimer() {
    if (isTimerRunning) {
        displayMessage("Error: Timer is already running.", false);
        return;
    }

    startTime = new Date();
    timerInterval = setInterval(updateTime, 1000);
    updateInterval = setInterval(updateServerTime, 1000);  // Update server every 1 second
    isTimerRunning = true;
}

function stopTimer() {
    if (!isTimerRunning) {
        displayMessage("Error: Timer is not running.", false);
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
            displayMessage(xhr.responseText.includes("successfully") ? "Account updated successfully." : "Failed to update account.", xhr.responseText.includes("successfully"));
            if (xhr.responseText.includes("successfully")) {
                hideEditAccount();
            }
        }
    };
    xhr.send(`username=${newUsername}&password=${newPassword}&class=${newClass}`);
}

function editUser(id) {
    editUserId = id;
    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/get_user.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            const user = JSON.parse(xhr.responseText);
            document.getElementById('editUsername').value = user.username;
            document.getElementById('editRole').value = user.role;
            document.getElementById('editClass').value = user.userClass;
            document.getElementById('editHours').value = user.hours;
            document.getElementById('editMinutes').value = user.minutes;
            document.getElementById('editSeconds').value = user.seconds;
            showEditUserForm();
        }
    };
    xhr.send(`id=${id}`);
}

function showEditUserForm() {
    document.getElementById('editUserForm').style.display = 'block';
}

function hideEditUserForm() {
    document.getElementById('editUserForm').style.display = 'none';
    document.getElementById('editUser').reset();  // Clear the form fields
}

function editUserDetails() {
    const username = document.getElementById('editUsername').value;
    const password = document.getElementById('editPassword').value;
    const role = document.getElementById('editRole').value;
    const userClass = document.getElementById('editClass').value;
    const hours = document.getElementById('editHours').value;
    const minutes = document.getElementById('editMinutes').value;
    const seconds = document.getElementById('editSeconds').value;

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/edit_user.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            displayMessage(xhr.responseText.includes("successfully") ? "User updated successfully." : "Failed to update user.", xhr.responseText.includes("successfully"));
            if (xhr.responseText.includes("successfully")) {
                hideEditUserForm();
                fetchUsers();  // Refresh user list
            }
        }
    };
    xhr.send(`id=${editUserId}&username=${username}&password=${password}&role=${role}&userClass=${userClass}&hours=${hours}&minutes=${minutes}&seconds=${seconds}`);
}

function registerUser() {
    const username = document.getElementById('regUsername').value;
    const password = document.getElementById('regPassword').value;
    const role = document.getElementById('regRole').value;
    const userClass = document.getElementById('regClass').value;

    if (role === 'student' && userClass.trim() === '') {
        displayMessage('Error: Students must enter a class.', false);
        return;
    }

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/register.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            const response = JSON.parse(xhr.responseText);
            displayMessage(response.message, response.status === "success");
            if (response.status === "success") {
                document.getElementById('registerForm').reset();  // Clear the form fields
            }
        }
    };
    xhr.send(`username=${username}&password=${password}&role=${role}&userClass=${userClass}`);
}

function loginUser() {
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;
    const role = document.getElementById('loginRole').value;

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/login.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            const response = JSON.parse(xhr.responseText);
            if (response.status === 'success') {
                window.location.href = response.redirect;
            } else {
                displayMessage(response.message, false);
            }
        }
    };
    xhr.send(`username=${username}&password=${password}&role=${role}`);
}

function fetchExistingTime() {
    fetch('php/get_existing_time.php')
        .then(response => response.json())
        .then(data => {
            existingHours = data.hours;
            existingMinutes = data.minutes;
            existingSeconds = data.seconds;
            updateDisplayedTime(existingHours, existingMinutes, existingSeconds);
        });
}

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
function deleteUser(id) {
    if (!confirm("Are you sure you want to delete this user?")) {
        return;
    }

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "php/delete_user.php", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            const response = JSON.parse(xhr.responseText);
            displayMessage(response.message, response.status === "success");
            if (response.status === "success") {
                fetchUsers();  // Refresh user list
            }
        }
    };
    xhr.send(`id=${id}`);
}


document.addEventListener('DOMContentLoaded', function() {
    fetchUsers();
    fetchExistingTime();  // Fetch and display existing time on page load
});