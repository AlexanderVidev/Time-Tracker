/* 
 * File:   User.h
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#ifndef USER_H
#define USER_H

#include <string>
#include <cstring>  // for strncpy

class User {
public:
    char username[21];  // Fixed size for binary I/O
    char password[21];
    char role[11];
    int hours;
    int minutes;
    int seconds;

    User() {
        std::memset(username, 0, sizeof(username));
        std::memset(password, 0, sizeof(password));
        std::memset(role, 0, sizeof(role));
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    User(std::string u, std::string p, std::string r, int h = 0, int m = 0, int s = 0) {
        std::strncpy(username, u.c_str(), 20);
        username[20] = '\0';
        std::strncpy(password, p.c_str(), 20);
        password[20] = '\0';
        std::strncpy(role, r.c_str(), 10);
        role[10] = '\0';
        hours = h;
        minutes = m;
        seconds = s;
    }
};

#endif // USER_H

