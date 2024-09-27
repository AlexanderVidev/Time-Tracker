/* 
 * File:   User.h
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#ifndef USER_H
#define USER_H

#include <cstring>  // For memset and strncpy
#include <string>
using namespace std;

class User {
public:
    char username[21];
    char password[21];
    char role[11];
    char userClass[21];  // Stores class information
    int hours;
    int minutes;
    int seconds;

    User() : hours(0), minutes(0), seconds(0) {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(role, 0, sizeof(role));
        memset(userClass, 0, sizeof(userClass));
    }

    User(string u, string p, string r, string cls = "", int h = 0, int m = 0, int s = 0) {
        strncpy(username, u.c_str(), 20);
        username[20] = '\0';
        strncpy(password, p.c_str(), 20);
        password[20] = '\0';
        strncpy(role, r.c_str(), 10);
        role[10] = '\0';
        strncpy(userClass, cls.c_str(), 20);
        userClass[20] = '\0';
        hours = h;
        minutes = m;
        seconds = s;
    }
};

#endif // USER_H