/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UserManager.cpp
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#include "UserManager.h"
#include <iostream>

void UserManager::loadUsers() {
    std::ifstream file("users.txt");
    std::string line, username, password, role;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> username >> password >> role;
        users.emplace_back(username, password, role);
    }
    file.close();
}

UserManager::UserManager() {
    loadUsers();
}

bool UserManager::authenticate(std::string username, std::string password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password)
            return true;
    }
    return false;
}

void UserManager::addUser(std::string username, std::string password, std::string role) {
    std::ofstream file("users.txt", std::ios::app);
    file << username << " " << password << " " << role << "\n";
    file.close();
    users.emplace_back(username, password, role);
}

void UserManager::deleteUser(std::string username) {
    std::ofstream file("users_tmp.txt");
    for (auto& user : users) {
        if (user.username != username) {
            file << user.username << " " << user.password << " " << user.role << "\n";
        }
    }
    file.close();
    std::remove("users.txt");
    std::rename("users_tmp.txt", "users.txt");
    loadUsers();
}

void UserManager::editUser(std::string username, std::string newPassword) {
    std::ofstream file("users_tmp.txt");
    for (auto& user : users) {
        if (user.username == username) {
            file << username << " " << newPassword << " " << user.role << "\n";
        } else {
            file << user.username << " " << user.password << " " << user.role << "\n";
        }
    }
    file.close();
    std::remove("users.txt");
    std::rename("users_tmp.txt", "users.txt");
    loadUsers();
}

void UserManager::viewUsers() {
    for (auto& user : users) {
        std::cout << "Username: " << user.username << ", Role: " << user.role << std::endl;
    }
}
