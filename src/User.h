
#if !defined(USER_H)
#define USER_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

class User {
public:
    virtual void FonctionPure() const = 0;
    User(const string &id, const string &lastName = "Entreprise", const string &firstName, const string &mail, const string &address, const string &password)
        : id(id), lastName(lastName), firstName(firstName), mail(mail), address(address), password(password) {
    }
    string getId() {
        return this->id;
    }
    string getPassword() {
        return this->password;
    }
    void setPassword(string password) {
        this->password = password;
    }
    void setMail(string mail) {
        this->mail = mail;
    }

protected:
    string id;
    void setId(string id) {
        this->id = id;
    }
    string lastName;
    string firstName;
    string mail;
    string address;
    string password;
};

#endif