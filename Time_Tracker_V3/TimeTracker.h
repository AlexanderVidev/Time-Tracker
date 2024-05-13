/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   TimeTracker.cpp
 * Author: alex
 * 
 * Created on MArch 26, 2024, 11:01 AM
 */


#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <ctime>
#include <string>

class TimeTracker {
private:
    time_t startTime; // Variable to store the start time
    bool running;     // Flag to check if the timer is running

public:
    TimeTracker();    // Constructor declaration
    void start();     // Start the timer
    void stop();      // Stop the timer and log the elapsed time
    void logTime(double seconds); // Log the time to a file in hours
    void displayTime(); // Display the total logged time
};

#endif // TIMETRACKER_H

