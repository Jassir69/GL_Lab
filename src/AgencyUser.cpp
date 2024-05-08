#include "AgencyUser.h"

#include <iostream>
#include <string>

AgencyUser::AgencyUser(string id, string lastName, string firstName, string mail, string address, string password) : User(id, lastName, firstName, mail, address, password) {
}