/** 
 * @file Menu.h
 * @brief Defines the Menu class which manages user interactions and menu navigation.
 * @author 
 * @date May 3, 2024
 */

#ifndef MENU_H
#define MENU_H

#include "UserManager.h"
#include "TimeTracker.h"
#include <string>
using namespace std;

/**
 * @class Menu
 * @brief Handles the main menu and submenus for user interactions.
 * 
 * This class is responsible for displaying different menus based on the user type (admin/user) and managing the user's navigation through these menus.
 */
class Menu {
public:
    /**
     * @brief Constructor for the Menu class.
     * @param userManager Reference to the UserManager to manage user data.
     * @param tracker Reference to the TimeTracker for tracking time.
     */
    Menu(UserManager& userManager, TimeTracker& tracker);

    /**
     * @brief Displays the main menu and handles user interactions.
     */
    void mainMenu();

private:
    UserManager& userManager; ///< UserManager object to manage user data.
    TimeTracker& tracker; ///< TimeTracker object to handle time tracking.

    void adminMenu(); ///< Displays the admin menu and handles admin interactions.
    void userMenu(); ///< Displays the user menu and handles regular user interactions.
    void displayMenu(const string& menuTitle, const vector<string>& options); ///< Generic menu display function.
    int getChoice(const string& prompt, int numOptions); ///< Retrieves and validates user menu choice.
    int getValidatedTimeInput(const string& prompt); ///< Ensures the user inputs valid time data.
};

#endif // MENU_H