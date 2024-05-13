/* 
 * File:   main.cpp
 * Author: Aleksandar Videv
 * Created on March 12, 2024, 10:36 PM
 * Purpose:  Time Tracker
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip> // Required for using std::setprecision to format floating point output

using namespace std;

class TimeTracker {
private:
    time_t startTime; // Variable to store the start time
    bool running;     // Flag to check if the timer is running

public:
    // Constructor initializes the timer as not running
    TimeTracker() : running(false) {}

    // Start the timer
    void start() {
        if (!running) {
            time(&startTime); // Set the current time to startTime
            running = true;   // Set running flag to true
            cout << "Timer started.\n";
        } else {
            cout << "Timer is already running.\n";
        }
    }

    // Stop the timer and log the elapsed time
    void stop() {
        if (running) {
            time_t endTime;
            time(&endTime); // Capture the stop time
            double elapsed = difftime(endTime, startTime); // Calculate the difference in seconds
            running = false; // Reset running flag
            logTime(elapsed); // Log the elapsed time to a file
            cout << "Timer stopped. Time logged: " << elapsed << " seconds.\n";
        } else {
            cout << "No timer is running.\n";
        }
    }

    // Log the time to a file in hours
    void logTime(double seconds) {
        ofstream logFile("timelog.txt", ios::app); // Open file in append mode
        logFile << fixed << setprecision(2) << seconds / 3600 << " hours\n"; // Write the time in hours
        logFile.close(); // Close the file
    }

    // Display the total logged time
    void displayTime() {
        ifstream logFile("timelog.txt"); // Open the log file
        if (!logFile.is_open()) {
            cout << "No time log available.\n";
            return;
        }

        string line;
        double totalHours = 0;
        cout << "Logged Hours:\n";
        while (getline(logFile, line)) {
            cout << line;
            totalHours += stod(line.substr(0, line.find(" hours"))); // Accumulate the total hours
        }
        cout << "Total Hours: " << fixed << setprecision(2) << totalHours << " hours\n";
        logFile.close(); // Close the file
    }
};

// Function to display menu and handle user inputs
void menu() {
    TimeTracker tracker; // Create a TimeTracker object
    char choice; // Variable to store user choice

    do {
        cout << "\nTime Tracker Menu\n";
        cout << "1. Start Timer\n";
        cout << "2. Stop Timer\n";
        cout << "3. Display Logged Time\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                tracker.start(); // Start the timer
                break;
            case '2':
                tracker.stop(); // Stop the timer
                break;
            case '3':
                tracker.displayTime(); // Display all logged time
                break;
            case '0':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '0');
}

int main() {
    menu(); // Call the menu function to start the program
    return 0;
}