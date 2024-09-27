/**
 * @file main.cpp
 * @brief Entry point for the Time Tracker application.
 *
 * Initializes the main components of the application including UserManager, TimeTracker, and Menu.
 * It sets up the relationships between these components and starts the user interaction process through the main menu.
 * @author Aleksandar Videv
 * @date March 12, 2024
 */

#include "Menu.h"
#include "UserManager.h"
#include "TimeTracker.h"

/**
 * @brief The main function that serves as the entry point of the application.
 * 
 * Sets up the user manager and time tracker, links them together, and launches the main menu.
 * @return Returns 0 upon successful completion.
 */
int main() {
    UserManager userManager;  // Instantiate the UserManager to manage user data.
    TimeTracker tracker;      // Create a TimeTracker to handle timing functionality.
    tracker.setUserManager(&userManager);  // Associate the UserManager with the TimeTracker.

    Menu menu(userManager, tracker);  // Create the main Menu with references to userManager and tracker.
    menu.mainMenu();  // Display the main menu and handle user interactions.

    return 0;  // Return 0 to indicate successful completion of the program.
}