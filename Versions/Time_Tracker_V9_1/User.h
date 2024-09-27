/** 
 * @file User.h
 * @brief Defines the User class for managing user details in the system.
 * @author alex
 * @date March 30, 2024
 */

#ifndef USER_H
#define USER_H

#include <cstring>  // Includes functions for memory manipulation
#include <string>
using namespace std;

/**
 * @class User
 * @brief Holds information about a system user, including credentials and time logged.
 *
 * This class stores details such as username, password, role, class information,
 * and the time duration for which the user has been active. It provides constructors
 * for initializing these values.
 */
class User {
public:
    char username[21]; ///< Username of the user, fixed size to ensure data consistency.
    char password[21]; ///< User's password, securely stored.
    char role[11]; ///< Role of the user (e.g., admin, student).
    char userClass[21]; ///< Class information, relevant for student users.
    int hours; ///< Hours part of the time logged by the user.
    int minutes; ///< Minutes part of the time logged by the user.
    int seconds; ///< Seconds part of the time logged by the user.

    /**
     * @brief Default constructor that initializes the user's properties to zero or empty.
     *
     * Initializes numeric time values to zero and character arrays to empty strings,
     * ensuring that all user properties start from a clean state.
     */
    User() : hours(0), minutes(0), seconds(0) {
        memset(username, 0, sizeof(username)); // Clear username array
        memset(password, 0, sizeof(password)); // Clear password array
        memset(role, 0, sizeof(role)); // Clear role array
        memset(userClass, 0, sizeof(userClass)); // Clear class information array
    }

    /**
     * @brief Parameterized constructor for creating a user with detailed information.
     * @param u Username of the user.
     * @param p Password of the user.
     * @param r Role of the user.
     * @param cls Class of the user, optional with default empty.
     * @param h Hours logged, optional with default 0.
     * @param m Minutes logged, optional with default 0.
     * @param s Seconds logged, optional with default 0.
     *
     * This constructor initializes the user with provided details, ensuring
     * that string lengths are handled correctly to fit into fixed-size character arrays.
     */
    User(string u, string p, string r, string cls = "", int h = 0, int m = 0, int s = 0) {
        strncpy(username, u.c_str(), 20); // Copy username, ensuring it does not exceed buffer size
        username[20] = '\0'; // Null terminate username array
        strncpy(password, p.c_str(), 20); // Copy password similarly
        password[20] = '\0'; // Null terminate password array
        strncpy(role, r.c_str(), 10); // Copy role
        role[10] = '\0'; // Null terminate role array
        strncpy(userClass, cls.c_str(), 20); // Copy class information
        userClass[20] = '\0'; // Null terminate class array
        hours = h; // Set hours
        minutes = m; // Set minutes
        seconds = s; // Set seconds
    }
};

#endif // USER_H