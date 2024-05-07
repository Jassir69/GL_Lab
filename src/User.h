
#if !defined(USER_H)
#define USER_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

class User {
public:
    virtual void FonctionPure() const = 0;

protected:
    string id;
    string lastName;
    string firstName;
    string mail;
    string address;
    string password;
};

#endif