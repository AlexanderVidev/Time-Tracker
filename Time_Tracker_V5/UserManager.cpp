/* 
 * File:   UserManager.cpp
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  // Include for remove_if
using namespace std;

void UserManager::saveUserData() {
    writeUsersToFile();  // Encapsulate file writing
}

UserManager::UserManager() {
    loadUsers();
}

void UserManager::writeUsersToFile() {
    ofstream file("users.dat", ios::binary | ios::out);
    if (!file) {
        cerr << "Failed to open file for writing.\n";
        return;
    }

    for (const auto& user : users) {
        file.write(user.username.c_str(), 20);  // Assuming username is fixed to 20 characters
        file.write(user.password.c_str(), 20);  // Assuming password is fixed to 20 characters
        file.write(user.role.c_str(), 10);      // Assuming role is fixed to 10 characters

        for (auto& user : users) {
            file.write(reinterpret_cast<char*>(&user.hours), sizeof(int));
            file.write(reinterpret_cast<char*>(&user.minutes), sizeof(int));
            file.write(reinterpret_cast<char*>(&user.seconds), sizeof(int));
        }

    }
    file.close();
}


void UserManager::loadUsers() {
    ifstream file("users.dat", ios::binary | ios::in);
    if (!file) {
        cerr << "Failed to open file for reading.\n";
        return;
    }

    User user;
    char username[21], password[21], role[11]; // Extra space for null terminator
    while (file.read(username, 20)) {
        username[20] = '\0';
        file.read(password, 20);
        password[20] = '\0';
        file.read(role, 10);
        role[10] = '\0';

        file.read(reinterpret_cast<char*>(&user.hours), sizeof(int));
        file.read(reinterpret_cast<char*>(&user.minutes), sizeof(int));
        file.read(reinterpret_cast<char*>(&user.seconds), sizeof(int));

        users.emplace_back(string(username), string(password), string(role), user.hours, user.minutes, user.seconds);
    }
    file.close();
}


User* UserManager::getUser(const string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;  // Return nullptr if no user is found
}

void UserManager::editUserTime(const string& username, int hours, int minutes, int seconds) {
    for (auto& user : users) {
        if (user.username == username) {
            user.hours = hours;
            user.minutes = minutes;
            user.seconds = seconds;
            writeUsersToFile();
            cout << "User time updated successfully.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

bool UserManager::authenticateWithRole(const string& username, const string& password, const string& role) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password && user.role == role)
            return true;
    }
    return false;
}

bool UserManager::userExists(const string& username) {
    for (const auto& user : users) {
        if (user.username == username)
            return true;
    }
    return false;
}

void UserManager::viewUsers() {
    if (users.empty()) {
        cout << "No users available.\n";
        return;
    }
    for (const auto& user : users) {
        if (user.role == "student") {  // Assuming only students have time logs
            cout << "Username: " << user.username << ", Role: " << user.role
                 << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s\n";
        } else {
            cout << "Username: " << user.username << ", Role: " << user.role << "\n";
        }
    }
}

void UserManager::addUser(string username, string password, string role, int hours, int minutes, int seconds) {
    if (!userExists(username)) {
        // Only add time tracking for students
        if (role == "student") {
            users.emplace_back(username, password, role, hours, minutes, seconds);
        } else {
            users.emplace_back(username, password, role);
        }
        writeUsersToFile();  // Update file with new user data including time tracking if applicable
    } else {
        cout << "An account with that username already exists. Please choose a different username.\n";
    }
}

bool UserManager::createUser() {
    string username, password, role, input;

    cout << "Create a new account.\n";
    cout << "Enter username: ";
    getline(cin, username);
    if (!userExists(username)) {
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter role (S for Student, I for Instructor): ";
        getline(cin, input);
        char roleChoice = input.length() > 0 ? input[0] : ' ';
        switch (roleChoice) {
            case 'S':
            case 's':
                role = "student";
                break;
            case 'I':
            case 'i':
                role = "instructor";
                break;
            default:
                cout << "Invalid role. Only 'S' for Student or 'I' for Instructor are allowed.\n";
                return false;
        }
        addUser(username, password, role); // Call addUser without time parameters
        cout << "Account successfully created as " << role << ".\n";
        return true;
    } else {
        cout << "An account with that username already exists. Please choose a different username.\n";
        return false;
    }
}

void UserManager::editUser(string oldUsername, string newUsername, string newPassword) {
    // Ensure the new username does not conflict with an existing username (unless it's the same user)
    if (!newUsername.empty() && newUsername != oldUsername && userExists(newUsername)) {
        cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    for (auto& user : users) {
        if (user.username == oldUsername) {
            if (!newUsername.empty() && newUsername != oldUsername) {
                user.username = newUsername;  // Update the username if it is new and valid
            }
            if (!newPassword.empty()) {
                user.password = newPassword;  // Update the password if a new one is provided
            }
            writeUsersToFile();
            cout << "User details updated successfully.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void UserManager::deleteUser(string username) {
    users.erase(remove_if(users.begin(), users.end(), [&username](const User& user) {
        return user.username == username;
    }), users.end());
    writeUsersToFile();
}