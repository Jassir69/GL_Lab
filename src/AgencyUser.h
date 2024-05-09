#if !defined(AGENCYUSER_H)
#define AGENCYUSER_H

#include <iostream>

#include "User.h"

class AgencyUser : public User {
public:
    AgencyUser(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password);
};

#endif