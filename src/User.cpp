using namespace std;
#include "User.h"

#include <iostream>
#include <string>

User::User(string id, string lastName, string firstName, string mail, string address, string password)
    : id(id), lastName(lastName), firstName(firstName), mail(mail), address(address), password(password) {
}
string User::getId() {
    return this->id;
}
string User::getPassword() {
    return this->password;
}
void User::setPassword(string password) {
    this->password = password;
}
void User::setMail(string mail) {
    this->mail = mail;
}

void User::setId(string id) {
    this->id = id;
}