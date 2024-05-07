#ifndef PROVIDER_H
#define PROVIDER_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Cleaner.h"
#include "User.h"

class Provider : public User
{
public:
    Provider(const string &id, const string &lastName = "Entreprise", const string &firstName, const string &mail, const string &address, const string &password)
        : User(id, lastName, firstName, mail, address, password)
    {
    }

protected:
    // liste de cleaner
    vector<Cleaner> cleaners;
};

#endif