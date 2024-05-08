#include "PrivateIndividual.h"

#include <iostream>
#include <string>

PrivateIndividual::PrivateIndividual(string id, string lastName, string firstName, string mail, string address, string password) : User(id, lastName, firstName, mail, address, password) {
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