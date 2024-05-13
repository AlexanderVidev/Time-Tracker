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

        for (User& user : users) {
            encryptUser(user);  // Encrypt user data
            userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));
            decryptUser(user);  // Decrypt data back to normal after writing
        }

        userFile.flush(); // Ensure data is written to disk
    } else {
        cerr << "File not open for writing." << endl;
    }
}

void UserManager::encryptUser(User& user) {
    char key = 'K'; // Simple encryption key
    for (size_t i = 0; i < sizeof(User); ++i) {
        reinterpret_cast<char*>(&user)[i] ^= key;
    }
}

// Decryption function to restore user data
void UserManager::decryptUser(User& user) {
    encryptUser(user); // Since XOR is its own inverse
}

void UserManager::writeUsersToFile() {
    userFile.close();  // Close the current file handle
    userFile.open("users.dat", ios::binary | ios::out | ios::trunc);  // Open in truncate mode to clear the file

    if (!userFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    for (auto& user : users) {
        encryptUser(user);  // Encrypt user data
        userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));  // Write the encrypted data
        decryptUser(user);  // Decrypt data in memory to retain original state
    }

    userFile.flush();  // Flush to ensure all data is written to the file
    userFile.close();  // Close the file
    userFile.open("users.dat", ios::binary | ios::in | ios::out);  // Reopen the file for reading and writing
}

void UserManager::loadUsers() {
    std::ifstream file("users.dat", ios::binary);
    if (!file) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        decryptUser(user);  // Decrypt user data after reading
        users.push_back(user);  // Add user to the vector
    }
    file.close();  // Close the file after reading
}

User* UserManager::getUser(const string& username) {
    for (auto& user : users) {
        if (strcmp(user.username, username.c_str()) == 0) {
            return &user;
        }
    }
    return nullptr;  // Return nullptr if no user is found
}

void UserManager::editUserTime(const string& username, int hours, int minutes, int seconds) {
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
    return any_of(users.begin(), users.end(), [&username](const User& user) {
        return strcmp(user.username, username.c_str()) == 0;
    });
}

void UserManager::viewUsers() {
    if (users.empty()) {
        cout << "No users available.\n";
        return;
    }
    for (const auto& user : users) {
        cout << "Username: " << user.username << ", Role: " << user.role;
        if (strcmp(user.role, "student") == 0) {  // Check if the user is a student
            cout << ", Class: " << user.userClass;  // Display class information for students
            cout << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s";  // Only display time for students
        }
        cout << "\n";  // Ensure each user entry is on a new line
    }
}

void UserManager::viewUsersByRole(const string& inputRole) {
    string role;
    // Normalize the input to handle different possible inputs for roles
    if (inputRole == "s" || inputRole == "S" || inputRole == "student" || inputRole == "Student" || inputRole == "STUDENT") {
        role = "student";
    } else if (inputRole == "i" || inputRole == "I" || inputRole == "instructor" || inputRole == "Instructor" || inputRole == "INSTRUCTOR") {
        role = "instructor";
    } else {
        cout << "Invalid role input. Please enter 's' for Student or 'i' for Instructor.\n";
        return;
    }

    bool found = false;
    for (const auto& user : users) {
        if (user.role == role) {
            found = true;
            cout << "Username: " << user.username << ", Role: " << user.role;
            if (role == "student") {
                cout << ", Class: " << user.userClass;
            }
            cout << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s\n";
        }
    }
    if (!found) {
        cout << "No users found with role " << role << ".\n";
    }
}


void UserManager::viewUsersByClass(const string& userClass) {
    bool found = false;
    for (const auto& user : users) {
        if (user.userClass == userClass) {
            found = true;
            cout << "Username: " << user.username << ", Class: " << user.userClass 
                 << ", Role: " << user.role << ", Time: " 
                 << user.hours << "h " << user.minutes << "m " << user.seconds << "s\n";
        }
    }
    if (!found) {
        cout << "No users found in class " << userClass << ".\n";
    }
}

void UserManager::addUser(string username, string password, string role, string userClass, int hours, int minutes, int seconds) {
    if (!userExists(username)) {
        User newUser(username, password, role, userClass, hours, minutes, seconds);
        users.push_back(newUser);
        writeUsersToFile(); // Ensure the file is updated with new user info
    } else {
        cout << "An account with that username already exists.\n";
    }
}

bool UserManager::createUser() {
    string username, password, role, userClass, input;

    cout << "Create a new account.\n";
    cout << "Enter username: ";
    getline(cin, username);
    if (userExists(username)) {
        cout << "An account with that username already exists. Please choose a different username.\n";
        return false;
    }

    cout << "Enter password: ";
    getline(cin, password);

    cout << "Enter role (S for Student, I for Instructor): ";
    getline(cin, input);
    char roleChoice = input.length() > 0 ? input[0] : ' ';
    switch (roleChoice) {
        case 'S':
        case 's':
            role = "student";
            cout << "Enter class: ";
            getline(cin, userClass);  // Prompt for class
            break;
        case 'I':
        case 'i':
            role = "instructor";
            break;
        default:
            cout << "Invalid role. Only 'S' for Student or 'I' for Instructor are allowed.\n";
            return false;
    }

    addUser(username, password, role, userClass);  // Pass class info to addUser
    cout << "Account successfully created as " << role << ".\n";
    return true;
}

void UserManager::editUser(string oldUsername, string newUsername, string newPassword, string newRole, string newUserClass) {
    for (auto& user : users) {
        if (strcmp(user.username, oldUsername.c_str()) == 0) {
            bool roleChangedToStudent = (!newRole.empty() && newRole == "student" && strcmp(user.role, "student") != 0);
            bool isCurrentlyStudent = strcmp(user.role, "student") == 0;
            
            if (!newUsername.empty() && newUsername != oldUsername && !userExists(newUsername)) {
                strncpy(user.username, newUsername.c_str(), 20); // Update the username
                user.username[20] = '\0'; // Ensure null termination
            }
            if (!newPassword.empty()) {
                strncpy(user.password, newPassword.c_str(), 20); // Update the password
                user.password[20] = '\0'; // Ensure null termination
            }
            if (!newRole.empty()) {
                strncpy(user.role, newRole.c_str(), 10); // Update the role
                user.role[10] = '\0'; // Ensure null termination
            }
            
            // Request class information if the user is changing to or is a student
            if (roleChangedToStudent || isCurrentlyStudent) {
                if (newUserClass.empty()) {
                    cout << "Enter new class for student: ";
                    getline(cin, newUserClass);
                }
                if (!newUserClass.empty()) {
                    strncpy(user.userClass, newUserClass.c_str(), 20); // Update the class
                    user.userClass[20] = '\0'; // Ensure null termination
                }
            } else if (!newUserClass.empty()) { // If class info provided, update it regardless
                strncpy(user.userClass, newUserClass.c_str(), 20);
                user.userClass[20] = '\0';
            }

            writeUsersToFile();
            cout << "User details updated successfully.\n";
            return;
        }
    }
    cout << "User not found. No changes made.\n";
}

void UserManager::deleteUser(string username) {
    // Using remove_if to filter out the user to delete
    auto originalSize = users.size();
    auto it = remove_if(users.begin(), users.end(), [&username](const User& user) {
        return username == user.username;  // Comparing username directly, assuming username is a string in your User class
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
