let startTime;
let timerInterval;

function startTimer() {
    startTime = new Date();
    timerInterval = setInterval(updateTime, 1000);
    document.getElementById('loggedTime').innerText = 'Timer started...';
}

function stopTimer() {
    clearInterval(timerInterval);
    const endTime = new Date();
    const elapsed = Math.floor((endTime - startTime) / 1000);
    const hours = Math.floor(elapsed / 3600);
    const minutes = Math.floor((elapsed % 3600) / 60);
    const seconds = elapsed % 60;
    document.getElementById('loggedTime').innerText = `Logged Time: ${hours}h ${minutes}m ${seconds}s`;
}

function updateTime() {
    const currentTime = new Date();
    const elapsed = Math.floor((currentTime - startTime) / 1000);
    const hours = Math.floor(elapsed / 3600);
    const minutes = Math.floor((elapsed % 3600) / 60);
    const seconds = elapsed % 60;
    document.getElementById('loggedTime').innerText = `Logged Time: ${hours}h ${minutes}m ${seconds}s`;
}
