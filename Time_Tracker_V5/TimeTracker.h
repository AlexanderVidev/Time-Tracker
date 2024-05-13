/* 
 * File:   TimeTracker.h
 * Author: alex
 * 
 * Created on MArch 26, 2024, 11:01 AM
 */

#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include "User.h"
#include "UserManager.h"
#include <chrono>
using namespace std;

class TimeTracker {
private:
    User* currentUser;
    UserManager* userManager;
    chrono::time_point<chrono::system_clock> startTime;
    bool tracking = false; 
    
    void normalizeTime(int& hours, int& minutes, int& seconds); // Private method for normalizing time

public:
    TimeTracker() : currentUser(nullptr), userManager(nullptr) {}
    void setUser(User* user) { currentUser = user; }
    void setUserManager(UserManager* um) { userManager = um; }
    User* getCurrentUser() const { return currentUser; }
    void start();
    void stop();
    void displayTime();
};

#endif // TIMETRACKER_H

