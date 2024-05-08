#ifndef PRIVATEINDIVIDUAL_H
#define PRIVATEINDIVIDUAL_H

using namespace std;
#include <iostream>
#include <vector>

#include "Sensor.h"
#include "User.h"

class PrivateIndividual : public User {
public:
    PrivateIndividual(const string &id, const string &lastName, const string &firstName, const string &mail, const string &address, const string &password);
    void setBan(bool ban);
    void addSensor(const Sensor &sensor);
    const vector<Sensor> &getSensors() const;

protected:
    vector<Sensor> sensors;
    bool isBan = 0;
};
#endif