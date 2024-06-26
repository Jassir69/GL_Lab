#ifndef PROVIDER_H
#define PROVIDER_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Cleaner.h"
#include "User.h"

class Provider : public User {
public:
    Provider(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password);

protected:
    // liste de cleaner
    std::vector<Cleaner> cleaners;
};

#endif