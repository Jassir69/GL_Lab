#include "Provider.h"

#include <iostream>
#include <string>

Provider::Provider(string id, string lastName, string firstName, string mail, string address, string password) : User(id, lastName, firstName, mail, address, password) {
}