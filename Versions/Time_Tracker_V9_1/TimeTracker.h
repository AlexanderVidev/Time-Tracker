/** 
 * @file TimeTracker.h
 * @brief Defines the TimeTracker class for managing time tracking for users.
 * @author alex
 * @date March 26, 2024
 */

#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include "User.h"
#include "UserManager.h"
#include <ctime>  // Includes standard time functions
#include <string>

/**
 * @class TimeTracker
 * @brief Manages the tracking of user time sessions.
 * 
 * This class is responsible for starting, stopping, and displaying the time tracking
 * of a user's session. It utilizes time_t to track the start time of a session.
 */
class TimeTracker {
private:
    User* currentUser; ///< Pointer to the current user in session.
    UserManager* userManager; ///< Pointer to the UserManager to access user management functions.
    time_t startTime; ///< Stores the start time of the current tracking session using time_t instead of chrono.
    bool tracking; ///< Flag to check if time tracking is currently active.

    /**
     * @brief Normalizes the time to ensure minutes and seconds are within typical range.
     * @param hours Reference to the hours to adjust.
     * @param minutes Reference to the minutes to adjust.
     * @param seconds Reference to the seconds to adjust.
     * 
     * Ensures that seconds are less than 60 by rolling over excess into minutes, and similarly for minutes to hours.
     */
    void normalizeTime(int& hours, int& minutes, int& seconds);

public:
    /**
     * @brief Constructor, initializes pointers to nullptr.
     */
    TimeTracker() : currentUser(nullptr), userManager(nullptr) {}

    /**
     * @brief Sets the current user for the time tracking session.
     * @param user Pointer to the user to be set as current user.
     */
    void setUser(User* user) { currentUser = user; }

    /**
     * @brief Sets the user manager handling the users.
     * @param um Pointer to the UserManager.
     */
    void setUserManager(UserManager* um) { userManager = um; }

    /**
     * @brief Gets the current user involved in the time tracking session.
     * @return Pointer to the current user.
     */
    User* getCurrentUser() const { return currentUser; }

    void start(); ///< Starts the time tracking session.
    void stop(); ///< Stops the current time tracking session.
    void displayTime(); ///< Displays the accumulated time for the current session.
};

#endif // TIMETRACKER_H