/* 
 * File:   UserManager.h
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class UserManager {
private:
    vector<User> users;
    void loadUsers();
    void writeUsersToFile();

public:
    UserManager();
    User* getUser(const string& username);
    
    void viewUsers();
    bool createUser();
    void saveUserData();
    bool authenticate(string username, string password);
    bool authenticateWithRole(const string& username, const string& password, const string& role);
    bool userExists(const string& username);
    void addUser(string username, string password, string role, int hours = 0, int minutes = 0, int seconds = 0);
    void deleteUser(string username);
    void editUser(string oldUsername, string newUsername, string newPassword);
    void editUserTime(const string& username, int hours, int minutes, int seconds);
};

#endif // USERMANAGER_H
