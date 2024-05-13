/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
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

public:
    UserManager();
    bool authenticate(std::string username, std::string password);
    void addUser(std::string username, std::string password, std::string role);
    void deleteUser(std::string username);
    void editUser(std::string username, std::string newPassword);
    void viewUsers();
};

#endif // USERMANAGER_H


