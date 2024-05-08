#include "AgencyUser.h"

#include <iostream>
#include <string>

AgencyUser::AgencyUser(const string &id, const string &lastName = "Entreprise", const string &firstName, const string &mail, const string &address, const string &password)
    : User(id, lastName, firstName, mail, address, password) {
}