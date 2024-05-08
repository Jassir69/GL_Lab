#if !defined(AGENCYUSER_H)
#define AGENCYUSER_H

using namespace std;
#include <iostream>

#include "User.h"

class AgencyUser : public User {
public:
    AgencyUser(const string &id, const string &lastName = "Entreprise", const string &firstName, const string &mail, const string &address, const string &password);
};

#endif