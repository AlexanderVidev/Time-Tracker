/* 
 * File:   main.cpp
 * Author: Aleksandar Videv
 * Created on March 12, 2024, 10:36 PM
 * Purpose:  Time Tracker
 */

#include "TimeTracker.h"
#include <iostream>

using namespace std;

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
