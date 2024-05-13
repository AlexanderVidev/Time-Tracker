/* 
 * File:   TimeTracker.cpp
 * Author: alex
 * 
 * Created on MArch 26, 2024, 11:01 AM
 */

#include "TimeTracker.h"
#include <iostream>
using namespace std;

void TimeTracker::start() {
    if (!currentUser) {
        cout << "No user logged in.\n";
        return;
    }
    startTime = chrono::system_clock::now();
    tracking = true;
}

void TimeTracker::stop() {
    if (!tracking || !currentUser || !userManager) {
        cout << "Timer not started, no user logged in, or user manager not set.\n";
        return;
    }
    auto endTime = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = endTime - startTime;
    int elapsed_time = static_cast<int>(elapsed_seconds.count());

    currentUser->seconds += elapsed_time % 60;
    currentUser->minutes += (elapsed_time / 60) % 60;
    currentUser->hours += elapsed_time / 3600;

    normalizeTime(currentUser->hours, currentUser->minutes, currentUser->seconds);

    tracking = false;
    userManager->saveUserData();
}

void TimeTracker::displayTime() {
    if (!currentUser) {
        cout << "No user logged in.\n";
        return;
    }

    int hours = currentUser->hours;
    int minutes = currentUser->minutes;
    int seconds = currentUser->seconds;

    if (tracking) {
        auto currentTime = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = currentTime - startTime;
        int elapsed_time = static_cast<int>(elapsed_seconds.count());

        seconds += elapsed_time % 60;
        minutes += (elapsed_time / 60) % 60;
        hours += elapsed_time / 3600;

        normalizeTime(hours, minutes, seconds);
    }

    cout << "Logged Time: " << hours << "h " << minutes << "m " << seconds << "s\n";
}

void TimeTracker::normalizeTime(int& hours, int& minutes, int& seconds) {
    minutes += seconds / 60;
    seconds %= 60;
    hours += minutes / 60;
    minutes %= 60;
}