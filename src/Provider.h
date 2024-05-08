#ifndef PROVIDER_H
#define PROVIDER_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Cleaner.h"
#include "User.h"

class Provider : public User {
public:
    Provider(string id, string lastName, string firstName, string mail, string address, string password);

protected:
    // liste de cleaner
    vector<Cleaner> cleaners;
};

#endif