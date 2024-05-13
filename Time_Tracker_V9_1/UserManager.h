/** 
 * @file UserManager.h
 * @brief Defines the UserManager class for managing user accounts and interactions with user data files.
 * @author alex
 * @date March 30, 2024
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * @class UserManager
 * @brief Manages user operations such as authentication, user data retrieval, and user data persistence.
 *
 * Handles user-related tasks including adding, deleting, and editing users, as well as
 * authentication and viewing user details. It interfaces with a file system to persist user data.
 */
class UserManager {
private:
    vector<User> users; ///< Container for storing all user objects in memory.
    fstream userFile; ///< File stream for user data file operations.

    void loadUsers(); ///< Loads users from the file into the vector.
    void writeUsersToFile(); ///< Writes the user data from the vector back into the file.
    /**
     * @brief Encrypts user data using XOR encryption.
     * @param user User object to encrypt.
     */
    void encryptUser(User& user); ///< Encrypts user data to ensure privacy.

    /**
     * @brief Decrypts user data using XOR decryption.
     * @param user User object to decrypt.
     */
    void decryptUser(User& user); ///< Decrypts user data to make it readable.

public:
    UserManager(); ///< Constructor that initializes and loads users from a file.
    ~UserManager(); ///< Destructor that ensures any remaining user data is saved.

    /**
     * @brief Retrieves a user object by username.
     * @param username The username of the user to retrieve.
     * @return Pointer to the User object if found, nullptr otherwise.
     */
    User* getUser(const string& username);

    void viewUsers(); ///< Displays all users' information.
    bool createUser(); ///< Interactively creates a new user from console input.
    void saveUserData(); ///< Saves all user data to the file.
    
    /**
     * @brief Authenticates a user based on username and password.
     * @param username The username to authenticate.
     * @param password The password to authenticate.
     * @return True if authentication is successful, false otherwise.
     */
    bool authenticate(string username, string password);

    /**
     * @brief Authenticates a user with an additional role check.
     * @param username The username to authenticate.
     * @param password The password to authenticate.
     * @param role The role to validate against.
     * @return True if authentication and role check are successful, false otherwise.
     */
    bool authenticateWithRole(const string& username, const string& password, const string& role);

    /**
     * @brief Checks if a user exists by username.
     * @param username The username to check.
     * @return True if the user exists, false otherwise.
     */
    bool userExists(const string& username);

    /**
     * @brief Adds a new user with detailed information.
     * @param username The new user's username.
     * @param password The new user's password.
     * @param role The new user's role.
     * @param userClass The class information, relevant for students.
     * @param hours Initial hours logged, optional.
     * @param minutes Initial minutes logged, optional.
     * @param seconds Initial seconds logged, optional.
     */
    void addUser(string username, string password, string role, string userClass, int hours = 0, int minutes = 0, int seconds = 0);

    /**
     * @brief Deletes a user by username.
     * @param username The username of the user to delete.
     */
    void deleteUser(string username);

    /**
     * @brief Edits existing user details.
     * @param oldUsername The current username of the user.
     * @param newUsername The new username, if changing.
     * @param newPassword The new password, if changing.
     * @param newRole The new role, if changing.
     * @param newUserClass The new class information, if applicable.
     */
    void editUser(string oldUsername, string newUsername, string newPassword, string newRole = "", string newUserClass = "");

    /**
     * @brief Edits the time logged for a specific user.
     * @param username The username of the user whose time is being edited.
     * @param hours The new hours to set.
     * @param minutes The new minutes to set.
     * @param seconds The new seconds to set.
     */
    void editUserTime(const string& username, int hours, int minutes, int seconds);

    /**
     * @brief Views users filtered by their role.
     * @param role The role to filter users by (e.g., "student", "instructor").
     */
    void viewUsersByRole(const string& role);

    /**
     * @brief Views users filtered by their class.
     * @param userClass The class to filter users by.
     */
    void viewUsersByClass(const string& userClass);
};

#endif // USERMANAGER_H