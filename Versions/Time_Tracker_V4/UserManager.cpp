/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * File:   UserManager.cpp
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  // Include for std::remove_if

bool UserManager::authenticateWithRole(const std::string& username, const std::string& password, const std::string& role) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password && user.role == role)
            return true;
    }
    return false;
}

void UserManager::loadUsers() {
    std::ifstream file("users.txt");
    std::string line, username, password, role;
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> username >> password >> role) {
            users.emplace_back(username, password, role);
        }
    }
}

void UserManager::writeUsersToFile() {
    std::ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.username << " " << user.password << " " << user.role;
        if (user.role == "student") {
            file << " " << user.hours << ":" << user.minutes << ":" << user.seconds;
        }
        file << "\n";
    }
    file.close();
}


UserManager::UserManager() {
    loadUsers();
}

bool UserManager::userExists(const std::string& username) {
    for (const auto& user : users) {
        if (user.username == username)
            return true;
    }
    return false;
}

void UserManager::addUser(std::string username, std::string password, std::string role, int hours, int minutes, int seconds) {
    if (!userExists(username)) {
        // Only add time tracking for students
        if (role == "student") {
            users.emplace_back(username, password, role, hours, minutes, seconds);
        } else {
            users.emplace_back(username, password, role);
        }
        writeUsersToFile();  // Update file with new user data including time tracking if applicable
    } else {
        std::cout << "An account with that username already exists. Please choose a different username.\n";
    }
}

void UserManager::deleteUser(std::string username) {
    users.erase(std::remove_if(users.begin(), users.end(), [&username](const User& user) {
        return user.username == username;
    }), users.end());
    writeUsersToFile();
}

void UserManager::editUser(std::string username, std::string newPassword) {
    for (auto& user : users) {
        if (user.username == username) {
            user.password = newPassword;
        }
    }
    writeUsersToFile();
}

void UserManager::viewUsers() {
    if (users.empty()) {
        std::cout << "No users available.\n";
    }
    for (const auto& user : users) {
        std::cout << "Username: " << user.username << ", Role: " << user.role << std::endl;
    }
}

bool UserManager::createUser() {
    std::string username, password, role, input;
    int hours = 0, minutes = 0, seconds = 0;

    std::cout << "Create a new account.\n";
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    if (!userExists(username)) {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        std::cout << "Enter role (S for Student, I for Instructor): ";
        std::getline(std::cin, input);
        char roleChoice = input.length() > 0 ? input[0] : ' ';
        switch (roleChoice) {
            case 'S':
            case 's':
                role = "student";
                std::cout << "Enter time spent in lab (hours minutes seconds): ";
                std::cin >> hours >> minutes >> seconds;
                std::cin.ignore(); // Ignore remaining newline
                break;
            case 'I':
            case 'i':
                role = "instructor";
                break;
            default:
                std::cout << "Invalid role. Only 'S' for Student or 'I' for Instructor are allowed.\n";
                return false;
        }
        addUser(username, password, role, hours, minutes, seconds);
        std::cout << "Account successfully created as " << role << ".\n";
        return true;
    } else {
        std::cout << "An account with that username already exists. Please choose a different username.\n";
        return false;
    }
}
