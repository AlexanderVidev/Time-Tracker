/** 
 * @file TimeTracker.cpp
 * @brief Manages the tracking of time for users, including starting, stopping, and displaying logged time.
 * @author alex
 * @date March 26, 2024
 */

#include "TimeTracker.h"
#include <iostream>
#include <ctime>

using namespace std;

/**
 * @brief Starts the timer for the current user session.
 *
 * This function records the start time if no timer is currently running and a user is logged in.
 * If the timer is already running or no user is logged in, it outputs an appropriate message.
 */
void TimeTracker::start() {
    if (!currentUser) {
        // Check if a user is logged in before starting the timer
        cout << "No user logged in.\n";
        return;
    }
    if (tracking) {
        // Prevent starting a new timer if one is already running
        cout << "Error: Timer is already running.\n";
        return;
    }
    startTime = time(nullptr); // Capture the current time as the start time
    tracking = true; // Set tracking to true to indicate the timer is running
    cout << "Timer started.\n";
}


/**
 * @brief Stops the timer and logs the time elapsed since it was started.
 *
 * If the timer is running and a user is logged in, this function calculates the elapsed time, updates the user's
 * time record, and saves the changes. If no timer is running or no user is logged in, it outputs an error message.
 */
void TimeTracker::stop() {
    if (!tracking || !currentUser) {
        // Ensure that a timer is running and a user is logged in before stopping the timer
        cout << "Timer not started or no user logged in.\n";
        return;
    }

    time_t endTime = time(nullptr); // Capture the current time as the end time
    double elapsed_seconds = difftime(endTime, startTime); // Calculate elapsed time in seconds
    int elapsedHours = static_cast<int>(elapsed_seconds) / 3600;
    int elapsedMinutes = (static_cast<int>(elapsed_seconds) / 60) % 60;
    int elapsedSeconds = static_cast<int>(elapsed_seconds) % 60;

    // Update the user's logged time
    currentUser->hours += elapsedHours;
    currentUser->minutes += elapsedMinutes;
    currentUser->seconds += elapsedSeconds;

    // Normalize the time to ensure proper time format
    normalizeTime(currentUser->hours, currentUser->minutes, currentUser->seconds);

    userManager->saveUserData(); // Save the updated user data
    tracking = false; // Set tracking to false as the timer is stopped

    cout << "Timer stopped. Time logged: "
         << elapsedHours << "h " << elapsedMinutes << "m " << elapsedSeconds << "s\n";
}


/**
 * @brief Displays the total logged time for the current user.
 *
 * Outputs the total time logged by the user both from past sessions and any ongoing session.
 * If no user is logged in, it outputs an error message.
 */

void TimeTracker::displayTime() {
    if (!currentUser) {
        // Check if a user is logged in before displaying time
        cout << "No user logged in.\n";
        return;
    }

    int displayHours = currentUser->hours;
    int displayMinutes = currentUser->minutes;
    int displaySeconds = currentUser->seconds;

    if (tracking) {
        // Calculate additional time if the timer is currently running
        time_t currentTime = time(nullptr);
        double elapsed_seconds = difftime(currentTime, startTime);

        displaySeconds += static_cast<int>(elapsed_seconds) % 60;
        displayMinutes += (static_cast<int>(elapsed_seconds) / 60) % 60;
        displayHours += static_cast<int>(elapsed_seconds) / 3600;

        // Normalize time to handle overflow from seconds to minutes and minutes to hours
        normalizeTime(displayHours, displayMinutes, displaySeconds);
    }
    // Output the total time logged for the user, including the current session if applicable
    cout << "Logged Time: " << displayHours << "h " << displayMinutes << "m " << displaySeconds << "s\n";
}

/**
 * @brief Normalizes the time values, rolling over seconds to minutes and minutes to hours.
 *
 * Ensures that seconds and minutes do not exceed their maximum values by converting excess into the next highest unit.
 * @param hours Reference to the hours to be normalized.
 * @param minutes Reference to the minutes to be normalized.
 * @param seconds Reference to the seconds to be normalized.
 */

void TimeTracker::normalizeTime(int& hours, int& minutes, int& seconds) {
    minutes += seconds / 60; // Convert excess seconds into minutes
    seconds %= 60; // Keep the remainder of seconds after dividing by 60
    hours += minutes / 60; // Convert excess minutes into hours
    minutes %= 60; // Keep the remainder of minutes after dividing by 60
}