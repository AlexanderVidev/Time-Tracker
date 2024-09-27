/* 
 * File:   main.cpp
 * Author: Aleksandar Videv
 * Created on March 12, 2024, 10:36 PM
 * Purpose:  Time Tracker
 */

#include "TimeTracker.h"
#include "UserManager.h"
#include <iostream>
#include <string>

using namespace std;

void adminMenu(UserManager& userManager) {
    string choice;
    string username, password, role;

    do {
        cout << "\nAdmin Menu\n";
        cout << "1. View Users\n";
        cout << "2. Add User\n";
        cout << "3. Delete User\n";
        cout << "4. Edit User\n";
        cout << "0. Exit to Main Menu\n";
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice.length() == 1) {
            switch (choice[0]) {
                case '1':
                    userManager.viewUsers();
                    break;
                case '2':  // Add User
                    if (userManager.createUser()) {
                        std::cout << "User added successfully.\n";
                    } else {
                        std::cout << "Failed to add user. Please try again.\n";
                    }
                    break;
                case '3':
                    cout << "Enter username to delete: ";
                    getline(cin, username);
                    if (userManager.userExists(username)) {
                        userManager.deleteUser(username);
                        cout << "User deleted successfully.\n";
                    } else {
                        cout << "No such user exists.\n";
                    }
                    break;
                case '4':
                    cout << "Enter username to edit: ";
                    getline(cin, username);
                    if (userManager.userExists(username)) {
                        cout << "Enter new password: ";
                        getline(cin, password);
                        userManager.editUser(username, password);
                        cout << "User edited successfully.\n";
                    } else {
                        cout << "No such user exists.\n";
                    }
                    break;
                case '0':
                    return;  // Exit admin menu
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } else {
            cout << "Invalid choice. Please enter a single character.\n";
        }
    } while (true);  // Keep menu open until '0' is entered
}

void userMenu(TimeTracker& tracker) {
    char choice;

    do {
        cout << "\nUser Menu\n";
        cout << "1. Start Timer\n";
        cout << "2. Stop Timer\n";
        cout << "3. Display Logged Time\n";
        cout << "0. Exit to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                tracker.start();
                break;
            case '2':
                tracker.stop();
                break;
            case '3':
                tracker.displayTime();
                break;
            case '0':
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '0');
}

void mainMenu() {
    UserManager userManager;
    TimeTracker tracker;
    string username, password, role, input;
    char choice;
    bool isAuthenticated = false;  // Declare isAuthenticated in the proper scope

    do {
        cout << "\nMain Menu\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Create Account\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        getline(cin, input);  // Use getline to read the full line
        if (input.length() == 1) {
            choice = input[0];
        } else {
            cout << "Invalid choice. Please enter a single character.\n";
            continue;  // Skip the rest of the loop iteration
        }

        switch (choice) {
            case '1':  // Admin login
            case '2':  // User login
                while (true) {
                    cout << (choice == '1' ? "Admin" : "User") << " Login\n";
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    isAuthenticated = userManager.authenticateWithRole(username, password, choice == '1' ? "instructor" : "student");
                    if (isAuthenticated) {
                        choice == '1' ? adminMenu(userManager) : userMenu(tracker);
                        break;
                    } else {
                        cout << "Login failed. Incorrect credentials or access level.\n";
                        cout << "Press 'r' to retry, 'n' to create a new account, or any other key to return to the main menu: ";
                        getline(cin, input);
                        if (input == "r" || input == "R") {
                            continue;
                        } else if (input == "n" || input == "N") {
                            cout << "Redirecting to account creation...\n";
                            break;
                        } else {
                            break;
                        }
                    }
                }
                break;
            case '3':  // Create Account
                userManager.createUser();
                break;
            case '4':  // Exit
                cout << "Exiting program.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');
}

int main() {
    mainMenu();  // Start the program with the main menu
    return 0;
}