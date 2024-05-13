/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

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

class UserManager {
private:
    std::vector<User> users;
    void loadUsers();
    void writeUsersToFile(); // Handles writing users to a file

public:
    UserManager();
    bool authenticate(std::string username, std::string password);
    bool authenticateWithRole(const std::string& username, const std::string& password, const std::string& role);
    bool userExists(const std::string& username);
    void addUser(std::string username, std::string password, std::string role, int hours = 0, int minutes = 0, int seconds = 0);  // Updated declaration
    void deleteUser(std::string username);
    void editUser(std::string username, std::string newPassword);
    void viewUsers();
    bool createUser();
};

#endif // USERMANAGER_H





