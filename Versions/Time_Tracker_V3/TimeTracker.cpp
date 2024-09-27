/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   TimeTracker.cpp
 * Author: alex
 * 
 * Created on MArch 26, 2024, 11:01 AM
 */

#include "TimeTracker.h"
#include <fstream>
#include <iostream>
#include <iomanip> // Required for std::setprecision

using namespace std;

// Constructor initializes the timer as not running
TimeTracker::TimeTracker() : running(false) {}

// Start the timer
void TimeTracker::start() {
    if (!running) {
        time(&startTime);
        running = true;
        cout << "Timer started.\n";
    } else {
        cout << "Timer is already running.\n";
    }
}

// Stop the timer and log the elapsed time
void TimeTracker::stop() {
    if (running) {
        time_t endTime;
        time(&endTime);
        double elapsed = difftime(endTime, startTime);
        running = false;
        logTime(elapsed);
        cout << "Timer stopped. Time logged: " << elapsed << " seconds.\n";
    } else {
        cout << "No timer is running.\n";
    }
}

// Log the time to a file in hours
void TimeTracker::logTime(double seconds) {
    ofstream logFile("timelog.txt", ios::app);
    logFile << fixed << setprecision(2) << seconds / 3600 << " hours\n";
    logFile.close();
}

// Display the total logged time
void TimeTracker::displayTime() {
    ifstream logFile("timelog.txt");
    if (!logFile.is_open()) {
        cout << "No time log available.\n";
        return;
    }

    string line;
    double totalHours = 0;
    cout << "Logged Hours:\n";
    while (getline(logFile, line)) {
        cout << line;
        totalHours += stod(line.substr(0, line.find(" hours")));
    }
    cout << "Total Hours: " << fixed << setprecision(2) << totalHours << " hours\n";
    logFile.close();
}


