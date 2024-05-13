/* 
 * File:   TimeTracker.cpp
 * Author: alex
 * 
 * Created on MArch 26, 2024, 11:01 AM
 */

#include "TimeTracker.h"
#include <iostream>
#include <ctime>

using namespace std;

void TimeTracker::start() {
    if (!currentUser) {
        cout << "No user logged in.\n";
        return;
    }
    if (tracking) {
        cout << "Error: Timer is already running.\n";  // Display error if timer is already running
        return;
    }
    startTime = time(nullptr);  // Record the start time
    tracking = true;
    cout << "Timer started.\n";  // Confirm timer start for debugging
}

void TimeTracker::stop() {
    if (!tracking || !currentUser) {
        cout << "Timer not started or no user logged in.\n";
        return;
    }

    time_t endTime = time(nullptr); // Get the current time as the end time
    double elapsed_seconds = difftime(endTime, startTime); // Calculate the difference in seconds
    int elapsedHours = static_cast<int>(elapsed_seconds) / 3600; // Calculate hours
    int elapsedMinutes = (static_cast<int>(elapsed_seconds) / 60) % 60; // Calculate minutes
    int elapsedSeconds = static_cast<int>(elapsed_seconds) % 60; // Calculate seconds

    // Update the current user's time
    currentUser->hours += elapsedHours;
    currentUser->minutes += elapsedMinutes;
    currentUser->seconds += elapsedSeconds;

    // Normalize time to correct for any overflow (e.g., 60 seconds -> 1 minute)
    normalizeTime(currentUser->hours, currentUser->minutes, currentUser->seconds);

    // Save user data
    userManager->saveUserData();

    // Set tracking to false indicating the timer is no longer running
    tracking = false;

    // Output the time logged in this session
    cout << "Timer stopped. Time logged: "
         << elapsedHours << "h " << elapsedMinutes << "m " << elapsedSeconds << "s\n";
}

void TimeTracker::displayTime() {
    if (!currentUser) {
        cout << "No user logged in.\n";
        return;
    }

    int displayHours = currentUser->hours;
    int displayMinutes = currentUser->minutes;
    int displaySeconds = currentUser->seconds;

    if (tracking) {
        time_t currentTime = time(nullptr);
        double elapsed_seconds = difftime(currentTime, startTime);

        displaySeconds += static_cast<int>(elapsed_seconds) % 60;
        displayMinutes += (static_cast<int>(elapsed_seconds) / 60) % 60;
        displayHours += static_cast<int>(elapsed_seconds) / 3600;

        // Normalize time to handle overflow from seconds to minutes and minutes to hours
        normalizeTime(displayHours, displayMinutes, displaySeconds);
    }

    cout << "Logged Time: " << displayHours << "h " << displayMinutes << "m " << displaySeconds << "s\n";
}

void TimeTracker::normalizeTime(int& hours, int& minutes, int& seconds) {
    minutes += seconds / 60;
    seconds %= 60;
    hours += minutes / 60;
    minutes %= 60;
}