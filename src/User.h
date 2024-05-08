
#if !defined(USER_H)
#define USER_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

class User {
public:
    virtual void FonctionPure() const = 0;
    User(string id, string lastName, string firstName, string mail, string address, string password);
    string getId();
    string getPassword();
    void setPassword(string password);
    void setMail(string mail);

protected:
    string id;
    void setId(string id);
    string lastName;
    string firstName;
    string mail;
    string address;
    string password;
};

#endif