// Sensor.h
#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Date.h"
using namespace std;

class Sensor {
private:
    string id;
    double latitude;
    double longitude;
    map<string, vector<double>> measurements;

public:
    struct Measurement {
        Date timestamp;
        string sensorId;
        string attributeId;
        double value;
    };
    Sensor(const string &sensorId, double latitude, double longitude);

    void addMeasurement(const string &attributeId, double value);
    const map<string, vector<double>> &getMeasurements() const;
};

#endif  // SENSOR_H