/*
 * @file UserManager.cpp
 * @brief Implementation of the UserManager class that handles user management tasks like adding,
 *        deleting, and editing users, as well as loading and saving user data to a file.
 * @author alex
 * @date March 30 , 2024, 7:23 AM
 */

#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  // Include for remove_if
#include <cstring>  // for strlen, memset

using namespace std;


/**
 * @brief Destructor for UserManager.
 *
 * Ensures all user data is saved before the object is destroyed.
 */
UserManager::~UserManager() {
    saveUserData(); // Save any remaining data.
}

/**
 * @brief Constructor for UserManager.
 *
 * Opens the users.dat file or creates it if it does not exist, then loads existing user data.
 */
UserManager::UserManager() {
    userFile.open("users.dat", ios::binary | ios::in | ios::out | ios::ate); // Attempt to open an existing file.
    if (!userFile.is_open()) {
        std::cerr << "Failed to open users.dat. Attempting to create a new file." << std::endl;
        userFile.clear(); // Clear any error flags.
        userFile.open("users.dat", ios::binary | ios::out | ios::trunc); // Create a new file.
        userFile.close(); // Close the newly created file.
        userFile.open("users.dat", ios::binary | ios::in | ios::out); // Reopen with read/write permissions.
    }
    if (!userFile) {
        std::cerr << "Error: Unable to open or create the users file!" << std::endl;
        exit(1); // Exit if still unable to open or create the file.
    }
    loadUsers(); // Load users from the file.
}

/**
 * @brief Save user data to the file.
 *
 * This method encrypts each user's data and writes it to the binary file.
 * If the file is not open, it outputs an error message.
 */
void UserManager::saveUserData() {
    if (userFile.is_open()) {
        userFile.seekp(0); // Start writing from the beginning of the file.
        userFile.clear(); // Clear any error flags that might be set.

        for (User& user : users) {
            encryptUser(user);  // Encrypt the user data.
            userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));  // Write the encrypted data to the file.
            decryptUser(user);  // Decrypt the user data to restore original values.
        }

        userFile.flush(); // Ensure all data is written to the disk.
    } else {
        cerr << "File not open for writing." << endl;  // Error handling if file isn't open.
    }
}

/**
 * @brief Encrypts user data using XOR encryption.
 *
 * @param user Reference to user object to be encrypted.
 */
void UserManager::encryptUser(User& user) {
    char key = 'K'; // Encryption key, simple for demonstration.
    for (size_t i = 0; i < sizeof(User); ++i) {
        reinterpret_cast<char*>(&user)[i] ^= key;  // Apply XOR for each byte of user data.
    }
}

/**
 * @brief Decrypts user data.
 *
 * This function uses the same encryptUser function to decrypt because XOR is its own inverse.
 * @param user Reference to user object to be decrypted.
 */
void UserManager::decryptUser(User& user) {
    encryptUser(user); // Decrypt by re-applying the XOR encryption.
}

/**
 * @brief Writes encrypted users data to a file.
 *
 * This method handles the file operations required to write all user data after encrypting it.
 */
void UserManager::writeUsersToFile() {
    userFile.close();  // Ensure the file is not already open.
    userFile.open("users.dat", ios::binary | ios::out | ios::trunc);  // Open file in binary mode to write from scratch.

    if (!userFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    for (auto& user : users) {
        encryptUser(user);  // Encrypt each user's data.
        userFile.write(reinterpret_cast<const char*>(&user), sizeof(User));  // Write the encrypted data.
        decryptUser(user);  // Decrypt the data to retain the original state in memory.
    }

    userFile.flush();  // Flush the stream to ensure all data is written.
    userFile.close();  // Close the file after writing.
    userFile.open("users.dat", ios::binary | ios::in | ios::out);  // Reopen file for both reading and writing.
}

/**
 * @brief Loads users data from a file.
 *
 * This function reads encrypted user data from a file, decrypts it, and adds it to the users vector.
 * If the file fails to open, it prints an error message.
 */
void UserManager::loadUsers() {
    std::ifstream file("users.dat", ios::binary); // Open the file in binary read mode.

    if (!file) {
        std::cerr << "Failed to open file for reading." << std::endl; // Error handling if file isn't open.
        return;
    }

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        decryptUser(user);  // Decrypt user data after reading from the file.
        users.push_back(user);  // Add the decrypted user to the vector of users.
    }
    file.close();  // Close the file after all users have been read.
}

/**
 * @brief Retrieves a user object by username.
 *
 * Searches for a user by username in the list of users. Returns a pointer to the User object if found,
 * otherwise returns nullptr.
 * @param username The username of the user to find.
 * @return A pointer to the User object or nullptr if not found.
 */
User* UserManager::getUser(const string& username) {
    for (auto& user : users) {
        if (strcmp(user.username, username.c_str()) == 0) {
            return &user;  // Return the address of the user if found
        }
    }
    return nullptr;  // Return nullptr if no user is found
}

/**
 * @brief Edits the time logged for a specific user.
 *
 * First normalizes the provided time values (hours, minutes, and seconds) and then updates the
 * specified user's logged time if they exist in the system.
 * @param username The username of the user whose time needs updating.
 * @param hours The number of hours to set.
 * @param minutes The number of minutes to set.
 * @param seconds The number of seconds to set.
 */
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


/**
 * @brief Authenticates a user with a specific role.
 * 
 * Checks if there exists a user with the given username, password, and role.
 * @param username The username of the user.
 * @param password The password of the user.
 * @param role The role of the user.
 * @return True if such a user exists, otherwise false.
 */
bool UserManager::authenticateWithRole(const string& username, const string& password, const string& role) {
    for (const auto& user : users) {
        if (strcmp(user.username, username.c_str()) == 0 && 
            strcmp(user.password, password.c_str()) == 0 && 
            strcmp(user.role, role.c_str()) == 0) {
            return true;  // User found and matches all credentials
        }
    }
    return false;  // No matching user found
}

/**
 * @brief Checks if a user exists based on username.
 * 
 * Searches for a user in the list by the username.
 * @param username The username to check against the user list.
 * @return True if the user exists, otherwise false.
 */
bool UserManager::userExists(const string& username) {
    return any_of(users.begin(), users.end(), [&username](const User& user) {
        return strcmp(user.username, username.c_str()) == 0;  // Compare the current user's username with the given one
    });
}

/**
 * @brief Displays all registered users along with their details.
 * 
 * Lists every user's username, role, class (if applicable), and time logged. It only displays
 * class and time for students.
 */
void UserManager::viewUsers() {
    if (users.empty()) {
        cout << "No users available.\n";  // Inform if no users are registered
        return;
    }
    for (const auto& user : users) {
        cout << "Username: " << user.username << ", Role: " << user.role;
        if (strcmp(user.role, "student") == 0) {
            cout << ", Class: " << user.userClass;  // Display class information if the user is a student
            cout << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s";
        }
        cout << "\n";
    }
}

/**
 * @brief Filters and displays users by their role.
 * 
 * Allows viewing of users grouped by a specified role such as 'student' or 'instructor'.
 * @param inputRole The role to filter the users by.
 */
void UserManager::viewUsersByRole(const string& inputRole) {
    string role;
    // Normalize input to handle different case inputs and partial inputs
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
                cout << ", Class: " << user.userClass;  // Display class if student
            }
            cout << ", Time: " << user.hours << "h " << user.minutes << "m " << user.seconds << "s\n";
        }
    }
    if (!found) {
        cout << "No users found with role " << role << ".\n";  // Inform if no users are found with the specified role
    }
}

/**
 * @brief Filters and displays users by their class.
 * 
 * Allows viewing of users grouped by a specified class, typically applicable to students.
 * @param userClass The class to filter the users by.
 */
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
        cout << "No users found in class " << userClass << ".\n"; // Notify if no users are found in the specified class
    }
}

/**
 * @brief Adds a new user to the system if they do not already exist.
 * 
 * Creates a new user with specified details and saves them to the system, ensuring no username duplication.
 * @param username The username for the new user.
 * @param password The password for the new user.
 * @param role The role of the new user (e.g., student, instructor).
 * @param userClass The class of the new user, relevant for students.
 * @param hours Initial hours logged (optional).
 * @param minutes Initial minutes logged (optional).
 * @param seconds Initial seconds logged (optional).
 */
void UserManager::addUser(string username, string password, string role, string userClass, int hours, int minutes, int seconds) {
    if (!userExists(username)) {
        User newUser(username, password, role, userClass, hours, minutes, seconds);
        users.push_back(newUser);
        writeUsersToFile(); // Persist the new user data
    } else {
        cout << "An account with that username already exists.\n";  // Notify if the username is already taken
    }
}

/**
 * @brief Interactively creates a new user based on console input.
 * 
 * Prompts for and receives user details from the console, then adds the user to the system if the username is not taken.
 * @return True if the user was created successfully, otherwise false.
 */
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
            getline(cin, userClass);  // Prompt for class if the role is student
            break;
        case 'I':
        case 'i':
            role = "instructor";
            break;
        default:
            cout << "Invalid role. Only 'S' for Student or 'I' for Instructor are allowed.\n";
            return false;
    }

    addUser(username, password, role, userClass);  // Add the new user
    cout << "Account successfully created as " << role << ".\n";
    return true;
}

/**
 * @brief Edits an existing user's details.
 * 
 * Allows modification of username, password, role, and class based on provided inputs. Ensures the new username is not already taken.
 * @param oldUsername The current username of the user to be edited.
 * @param newUsername The new username to update to, if provided.
 * @param newPassword The new password to update to, if provided.
 * @ant'semail.comwRole The new role to update to, if provided.
 * @param newUserClass The new class to update to, if applicable.
 */
void UserManager::editUser(string oldUsername, string newUsername, string newPassword, string newRole, string newUserClass) {
    for (auto& user : users) {
        if (strcmp(user.username, oldUsername.c_str()) == 0) {
            if (!newUsername.empty() && !userExists(newUsername)) {
                strncpy(user.username, newUsername.c_str(), 20);  // Update username if new one is not taken
                user.username[20] = '\0';
            }
            if (!newPassword.empty()) {
                strncpy(user.password, newPassword.c_str(), 20);  // Update password
                user.password[20] = '\0';
            }
            if (!newRole.empty()) {
                strncpy(user.role, newRole.c_str(), 10);  // Update role
                user.role[10] = '\0';
            }
            if (!newUserClass.empty()) {
                strncpy(user.userClass, newUserClass.c_str(), 20);  // Update class for students
                user.userClass[20] = '\0';
            }
            writeUsersToFile();  // Persist changes to disk
            cout << "User details updated successfully.\n";
            return;
        }
    }
    cout << "User not found. No changes made.\n";  // Notify if the specified user does not exist
}

/**
 * @brief Deletes a user from the system.
 * 
 * Removes a user with the specified username from the list and updates the user file.
 * @param username The username of the user to delete.
 */
void UserManager::deleteUser(string username) {
    auto it = remove_if(users.begin(), users.end(), [&username](const User& user) {
        return username == user.username;  // Find the user to delete
    });

    if (it != users.end()) {
        users.erase(it, users.end());  // Remove the user from the list
        writeUsersToFile();  // Update the file after removal
        cout << "User deleted successfully." << endl;
    } else {
        cout << "User not found. No user deleted." << endl;
    }
}