/* 
 * File:   Menu.h
 * Author: dvide
 *
 * Created on May 3, 2024, 5:20 AM
 */

#ifndef MENU_H
#define MENU_H

#include "UserManager.h"
#include "TimeTracker.h"
#include <string>
using namespace std;

class Menu {
public:
    Menu(UserManager& userManager, TimeTracker& tracker);
    void mainMenu();

private:
    UserManager& userManager;
    TimeTracker& tracker;

    void adminMenu();
    void userMenu();
    void displayMenu(const string& menuTitle, const vector<string>& options);
    int getChoice(const string& prompt, int numOptions);
    int getValidatedTimeInput(const string& prompt);
};

#endif // MENU_H
