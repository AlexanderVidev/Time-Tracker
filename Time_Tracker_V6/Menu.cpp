/* 
 * File:   Menu.cpp
 * Author: dvide
 * 
 * Created on May 3, 2024, 5:20 AM
 */

#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Menu::Menu(UserManager& userManager, TimeTracker& tracker) : userManager(userManager), tracker(tracker) {}

void Menu::mainMenu() {
    string input;
    bool exit = false;

    while (!exit) {
        cout << "\nMain Menu\n"
                  << "1. Admin Login\n"
                  << "2. User Login\n"
                  << "3. Create Account\n"
                  << "4. Exit\n"
                  << "Enter choice: ";
        getline(cin, input);

        switch (input[0]) {
            case '1': // Admin login
            case '2': // User login
                {
                    string username, password;
                    cout << (input[0] == '1' ? "Admin" : "User") << " Login\n"
                              << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    bool isAuthenticated = userManager.authenticateWithRole(username, password, input[0] == '1' ? "instructor" : "student");
                    if (isAuthenticated) {
                        User* loggedInUser = userManager.getUser(username);
                        tracker.setUser(loggedInUser);
                        if (input[0] == '1') {
                            adminMenu();
                        } else {
                            userMenu();
                        }
                    } else {
                        cout << "Incorrect credentials or access level.\n";
                    }
                    break;
                }
            case '3': // Create Account
                userManager.createUser();
                break;
            case '4': // Exit
                cout << "Exiting program.\n";
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Menu::adminMenu() {
    string choice;
    do {
        cout << "\nAdmin Menu\n"
                  << "1. View Users\n"
                  << "2. Add User\n"
                  << "3. Delete User\n"
                  << "4. Edit User\n"
                  << "5. Edit User Time\n"
                  << "0. Exit to Main Menu\n"
                  << "Enter choice: ";
        getline(cin, choice);

        switch (choice[0]) {
            case '1':
                userManager.viewUsers();
                break;
            case '2':
                userManager.createUser();
                break;
            case '3':
                {
                    string username;
                    cout << "Enter username to delete: ";
                    getline(cin, username);
                    userManager.deleteUser(username);
                    cout << "User deleted successfully.\n";
                }
                break;
            case '4':
                {
                    string username, newUsername, newPassword;
                    cout << "Enter username to edit: ";
                    getline(cin, username);
                    cout << "Enter new username (leave empty if unchanged): ";
                    getline(cin, newUsername);
                    cout << "Enter new password (leave empty if unchanged): ";
                    getline(cin, newPassword);
                    userManager.editUser(username, newUsername, newPassword);
                }
                break;
            case '5':
                {
                    string username;
                    int hours, minutes, seconds;
                    cout << "Enter username of the student to edit time: ";
                    getline(cin, username);
                    do {
                        cout << "Enter new hours (0-9999): ";
                        cin >> hours;
                        cout << "Enter new minutes (0-59): ";
                        cin >> minutes;
                        cout << "Enter new seconds (0-59): ";
                        cin >> seconds;
                        cin.ignore();  // Clear the newline character from the input buffer

                        if (hours < 0 || hours > 9999 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
                            cout << "Invalid time input. Please enter values within the valid range.\n";
                        } else {
                            break;  // Exit the loop if valid
                        }
                    } while (true);
                    userManager.editUserTime(username, hours, minutes, seconds);
                    cout << "User time updated successfully.\n";
                }
                break;
            case '0':
                return; // Exit admin menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

void Menu::userMenu() {
    string choice;
    do {
        cout << "\nUser Menu\n"
                  << "1. Start Timer\n"
                  << "2. Stop Timer\n"
                  << "3. Display Logged Time\n"
                  << "4. Edit Details\n"
                  << "0. Exit to Main Menu\n"
                  << "Enter choice: ";
        getline(cin, choice);

        switch (choice[0]) {
            case '1':
                tracker.start();
                break;
            case '2':
                tracker.stop();
                break;
            case '3':
                tracker.displayTime();
                break;
            case '4':
                {
                    User* user = tracker.getCurrentUser();
                    if (user) {
                        string newUsername, newPassword;
                        cout << "Enter new username (leave empty if unchanged): ";
                        getline(cin, newUsername);
                        cout << "Enter new password (leave empty if unchanged): ";
                        getline(cin, newPassword);
                        userManager.editUser(user->username, newUsername, newPassword);
                    } else {
                        cout << "No user logged in.\n";
                    }
                }
                break;
            case '0':
                return; // Exit user menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}