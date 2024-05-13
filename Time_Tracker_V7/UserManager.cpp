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
#include <cstring>  // for strlen, memset

using namespace std;

UserManager::~UserManager() {
    saveUserData(); // Save any remaining data
}

UserManager::UserManager() {
    userFile.open("users.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!userFile.is_open()) {
        cout << "Failed to open users.dat. Attempting to create a new file." << endl;
        userFile.clear(); // Clear any error flags
        userFile.open("users.dat", ios::binary | ios::out | ios::trunc); // Create a new file
        userFile.close(); // Close the file
        userFile.open("users.dat", ios::binary | ios::in | ios::out); // Reopen with read/write permissions
    }
    if (!userFile) {
        cerr << "Error: Unable to open or create the users file!" << endl;
        exit(1); // Exit or handle the error as needed
    }
    loadUsers(); // Load existing users from file
}

void UserManager::saveUserData() {
    if (userFile.is_open()) {
        userFile.seekp(0); // Start at the beginning of the file
        userFile.clear(); // Clear error flags

        for (const User& user : users) {
            userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));
        }

        userFile.flush(); // Ensure data is written to disk
    } else {
        cerr << "File not open for writing." << endl;
    }
}


void UserManager::writeUsersToFile() {
    userFile.close();  // Close the current file handle to reset its state
    userFile.open("users.dat", ios::binary | ios::out | ios::trunc);  // Open in truncate mode to clear the file

    if (!userFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    for (const auto& user : users) {
        userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));
    }

    userFile.flush();  // Make sure all data is written to the file
    userFile.close();  // Close and reopen the file for both reading and writing
    userFile.open("users.dat", ios::binary | ios::in | ios::out);
}

void UserManager::loadUsers() {
    std::ifstream file("users.dat", std::ios::binary | std::ios::in);
    if (!file) {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        users.push_back(user);
    }
    file.close();
}

User* UserManager::getUser(const string& username) {
    for (auto& user : users) {
        if (strcmp(user.username, username.c_str()) == 0) {
            return &user;
        }
    }
    return nullptr;  // Return nullptr if no user is found
}

void UserManager::editUserTime(const std::string& username, int hours, int minutes, int seconds) {
    // Normalize the entered time first
    minutes += seconds / 60;
    seconds %= 60;
    hours += minutes / 60;
    minutes %= 60;

    // Check if the user exists and update their time
    for (auto& user : users) {
        if (user.username == username) {
            user.hours = hours;
            user.minutes = minutes;
            user.seconds = seconds;
            writeUsersToFile(); // Save changes to file
            cout << "User time updated successfully.\n";
            return;  // Exit the function after successful update
        }
    }
    cout << "User not found. No time updated.\n";  // Notify if user not found
}

bool UserManager::authenticateWithRole(const string& username, const string& password, const string& role) {
    for (const auto& user : users) {
        if (strcmp(user.username, username.c_str()) == 0 && strcmp(user.password, password.c_str()) == 0 && strcmp(user.role, role.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

bool UserManager::userExists(const string& username) {
    return std::any_of(users.begin(), users.end(), [&username](const User& user) {
        return strcmp(user.username, username.c_str()) == 0;
    });
}

void UserManager::viewUsers() {
    if (users.empty()) {
        cout << "No users available.\n";
        return;
    }
    for (const auto& user : users) {
        if (strcmp(user.role, "student") == 0) {  // Assuming only students have time logs
            cout << "Username: " << user.username << ", Role: " << user.role
                 << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s\n";
        } else {
            cout << "Username: " << user.username << ", Role: " << user.role << "\n";
        }
    }
}

void UserManager::addUser(string username, string password, string role, int hours, int minutes, int seconds) {
    if (!userExists(username)) {
        User newUser(username, password, role, hours, minutes, seconds);
        users.push_back(newUser); // Add the new user to the vector
        writeUsersToFile(); // Write changes to the binary file
    } else {
        cout << "An account with that username already exists.\n";
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

void UserManager::editUser(std::string oldUsername, std::string newUsername, std::string newPassword) {
    // Ensure the new username does not conflict with an existing username (unless it's the same user)
    if (!newUsername.empty() && newUsername != oldUsername && userExists(newUsername)) {
        std::cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    for (auto& user : users) {
        if (strcmp(user.username, oldUsername.c_str()) == 0) {
            if (!newUsername.empty() && newUsername != oldUsername) {
                std::strncpy(user.username, newUsername.c_str(), 20); // Update the username if it is new and valid
                user.username[20] = '\0'; // Ensure null termination
            }
            if (!newPassword.empty()) {
                std::strncpy(user.password, newPassword.c_str(), 20); // Update the password if a new one is provided
                user.password[20] = '\0'; // Ensure null termination
            }
            writeUsersToFile();
            std::cout << "User details updated successfully.\n";
            return;
        }
    }
}

void UserManager::deleteUser(string username) {
    // Using std::remove_if to filter out the user to delete
    auto originalSize = users.size();
    auto it = remove_if(users.begin(), users.end(), [&username](const User& user) {
        return username == user.username;  // Comparing username directly, assuming username is a std::string in your User class
    });

    // Check if any users were removed
    if (it != users.end()) {
        users.erase(it, users.end());  // Erase the removed elements from the vector

        writeUsersToFile();  // Write the updated list back to the file

        cout << "User deleted successfully." << endl;
    } else {
        cout << "User not found. No user deleted." << endl;
    }
}