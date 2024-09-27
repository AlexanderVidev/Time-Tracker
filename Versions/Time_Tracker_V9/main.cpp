/* 
 * File:   main.cpp
 * Author: Aleksandar Videv
 * Created on March 12, 2024, 10:36 PM
 * Purpose:  Time Tracker
 */

#include "Menu.h"
#include "UserManager.h"
#include "TimeTracker.h"

int main() {
    UserManager userManager;
    TimeTracker tracker;
    tracker.setUserManager(&userManager);

    Menu menu(userManager, tracker);
    menu.mainMenu();

    return 0;
}