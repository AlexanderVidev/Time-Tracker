/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   User.h
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    std::string role;
    int hours;    // Time tracking for students
    int minutes;
    int seconds;

    // Constructor updated with time tracking fields, default values for time fields
    User(std::string username, std::string password, std::string role, int hours = 0, int minutes = 0, int seconds = 0)
        : username(username), password(password), role(role), hours(hours), minutes(minutes), seconds(seconds) {}
};

#endif // USER_H
