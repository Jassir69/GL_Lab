#ifndef PRIVATEINDIVIDUAL_H
#define PRIVATEINDIVIDUAL_H

using namespace std;
#include <iostream>
#include <vector>
#include "User.h"
#include "Sensor.h"

class PrivateIndividual : public User
{
public:
    PrivateIndividual(const string &id, const string &lastName, const string &firstName, const string &mail, const string &address, const string &password) : User(id, lastName, firstName, mail, address, password)
    {
    }
    void setBan(bool ban)
    {
        isBan = ban;
    }
    void addSensor(const Sensor &sensor)
    {
        sensors.push_back(sensor);
    }
    const vector<Sensor> &getSensors() const
    {
        return sensors;
    }

protected:
    vector<Sensor> sensors;
    bool isBan = 0;
};
#endif