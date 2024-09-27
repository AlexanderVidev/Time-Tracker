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
    char choice;
    string username, password, role;

    do {
        cout << "\nAdmin Menu\n";
        cout << "1. View Users\n";
        cout << "2. Add User\n";
        cout << "3. Delete User\n";
        cout << "4. Edit User\n";
        cout << "0. Exit to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                userManager.viewUsers();
                break;
            case '2':
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter role (student/instructor): ";
                cin >> role;
                userManager.addUser(username, password, role);
                break;
            case '3':
                cout << "Enter username to delete: ";
                cin >> username;
                userManager.deleteUser(username);
                break;
            case '4':
                cout << "Enter username to edit: ";
                cin >> username;
                cout << "Enter new password: ";
                cin >> password;
                userManager.editUser(username, password);
                break;
            case '0':
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '0');
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
    string username, password;
    bool isAuthenticated = false;
    char choice;

    do {
        cout << "\nMain Menu\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                while (true) {
                    cout << "Admin Login\n";
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    isAuthenticated = userManager.authenticate(username, password);
                    if (isAuthenticated) {
                        adminMenu(userManager);
                        break;
                    } else {
                        cout << "Login failed. Incorrect username or password.\n";
                        cout << "Press 'r' to retry, 'n' to create a new account, or any other key to return to the main menu: ";
                        char loginChoice;
                        cin >> loginChoice;
                        if (loginChoice == 'r' || loginChoice == 'R') {
                            continue;
                        } else if (loginChoice == 'n' || loginChoice == 'N') {
                            cout << "Redirecting to account creation...\n";
                            cout << "Enter username: ";
                            cin >> username;
                            if (!userManager.userExists(username)) {
                                cout << "Enter password: ";
                                cin >> password;
                                cout << "Enter role (student/instructor): ";
                                cin >> role;
                                userManager.addUser(username, password, role);
                                cout << "Account created successfully.\n";
                            } else {
                                cout << "An account with that username already exists. Please choose a different username.\n";
                            }
                            break;
                        } else {
                            break;
                        }
                    }
                }
                break;
            case '2':
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                isAuthenticated = userManager.authenticate(username, password);
                if (isAuthenticated) {
                    userMenu(tracker);
                } else {
                    cout << "Authentication failed. Try again.\n";
                }
                break;
            case '3':
                cout << "Exiting program.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '3');
}

int main() {
    mainMenu(); // Call the main menu function to start the program
    return 0;
}

