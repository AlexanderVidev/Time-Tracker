/* 
 * File:   User.h
 * Author: alex
 *
 * Created on March 30 , 2024, 7:23 AM
 */

#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    string username;
    string password;
    string role;
    int hours;
    int minutes;
    int seconds;

    User() : username(""), password(""), role(""), hours(0), minutes(0), seconds(0) {}

    User(string u, string p, string r, int h = 0, int m = 0, int s = 0)
        : username(u), password(p), role(r), hours(h), minutes(m), seconds(s) {}
};


#endif // USER_H