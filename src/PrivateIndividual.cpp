#include "PrivateIndividual.h"

#include <iostream>
#include <string>

PrivateIndividual::PrivateIndividual(const string &id, const string &lastName, const string &firstName, const string &mail, const string &address, const string &password)
    : User(id, lastName, firstName, mail, address, password) {
}

void PrivateIndividual::setBan(bool ban) {
    isBan = ban;
}
void PrivateIndividual::addSensor(const Sensor &sensor) {
    sensors.push_back(sensor);
}
const vector<Sensor> &PrivateIndividual::getSensors() const {
    return sensors;
}