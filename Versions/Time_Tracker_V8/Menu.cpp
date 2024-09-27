/* 
 * File:   Menu.cpp
 * Author: dvide
 * 
 * Created on May 3, 2024, 5:20 AM
 */

#include "TimeTracker.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Required for istringstream
#include <iomanip> // Required for get_time

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
        cout << endl;

        switch (choice[0]) {
            case '1':
                cout << "1. View All Users\n"
                     << "2. View by Role\n"
                     << "3. View by Class\n"  // Added option to view by class
                     << "Enter choice for view: ";
                getline(cin, choice);
                if (choice == "1") {
                    userManager.viewUsers();
                } else if (choice == "2") {
                    cout << "Choose role (s = Student, i = Instructor): ";
                    string role;
                    getline(cin, role);
                    userManager.viewUsersByRole(role);  // View users by normalized role
                } else if (choice == "3") {
                    cout << "Enter class to filter by: ";  // Prompt for class
                    string userClass;
                    getline(cin, userClass);
                    userManager.viewUsersByClass(userClass);  // View users by class
                }
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
                    if (userManager.userExists(username)) {
                       cout << "User deleted successfully.\n";              
                    }                 
                }
                break;
            case '4':
                {
                string username, newUsername, newPassword, newRole, newUserClass;
                char roleChoice;
                cout << "Enter username to edit: ";
                getline(cin, username);

                if (!userManager.userExists(username)) {
                    cout << "User not found.\n";
                    break;
                }
                cout << "Enter new username (leave empty if unchanged): ";
                getline(cin, newUsername);
                cout << "Enter new password (leave empty if unchanged): ";
                getline(cin, newPassword);

                // Adding a choice for the role
                cout << "Choose new role (1 for Student, 2 for Instructor, leave empty if unchanged): ";
                getline(cin, newRole);
                bool promptForClass = false;
                if (!newRole.empty()) {
                    roleChoice = newRole[0];
                    switch (roleChoice) {
                        case '1':
                            newRole = "student";
                            promptForClass = true; // Prompt for class if role is student
                            break;
                        case '2':
                            newRole = "instructor";
                            newUserClass = ""; // Clear class when role is instructor
                            break;
                        default:
                            cout << "Invalid role selected. No changes to role will be made.\n";
                            newRole = ""; // Reset to empty to avoid changing the role
                            promptForClass = true; // Still prompt for class if the role change is invalid
                            break;
                    }
                }

                // Prompt for class if role is student or role change is skipped
                if (promptForClass) {
                    cout << "Enter new class (leave empty if unchanged): ";
                    getline(cin, newUserClass);
                }

                userManager.editUser(username, newUsername, newPassword, newRole, newUserClass);
            }
                break;
            case '5': // Edit User Time
               {
                   string username;
                   cout << "Enter username of the user to edit time: ";
                   getline(cin, username);

                   // Check if user exists before asking for time details
                   if (!userManager.userExists(username)) {
                       cout << "User not found.\n";
                       break;  // Exit if user doesn't exist
                   }

                   int hours = getValidatedTimeInput("Enter new hours (0-9999): ");
                   int minutes = getValidatedTimeInput("Enter new minutes (0-59): ");
                   int seconds = getValidatedTimeInput("Enter new seconds (0-59): ");

                   userManager.editUserTime(username, hours, minutes, seconds);                  
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

int Menu::getValidatedTimeInput(const string& prompt) {
    string input;
    int time;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            time = stoi(input); // Convert string to integer
            if (prompt.find("hours") != string::npos && time >= 0 && time <= 9999) {
                break;
            } else if (time >= 0 && time <= 59) {
                break;
            } else {
                cout << "Invalid time. Please enter a valid number within the range.\n";
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a valid number.\n";
        } catch (const out_of_range& e) {
            cout << "Number out of range. Please enter a smaller number.\n";
        }
    }
    return time;
}