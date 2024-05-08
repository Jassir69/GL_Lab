#if !defined(AGENCYUSER_H)
#define AGENCYUSER_H

using namespace std;
#include <iostream>

#include "User.h"

class AgencyUser : public User {
public:
    AgencyUser(string id, string lastName, string firstName, string mail, string address, string password);
};

#endif