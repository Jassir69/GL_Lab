// Sensor.h
#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Date.h"

class Sensor
{
private:
    std::string id;
    double latitude;
    double longitude;
    std::map<std::string, std::vector<double>> measurements;

public:
    struct Measurement
    {
        Date timestamp;
        string sensorId;
        string attributeId;
        double value;
    };
    Sensor(const std::string &sensorId, double latitude, double longitude) : id(sensorId), latitude(latitude), longitude(longitude)
    {
    }

    void addMeasurement(const std::string &attributeId, double value)
    {
        measurements[attributeId].push_back(value);
    }

    const std::map<std::string, std::vector<double>> &getMeasurements() const
    {
        return measurements;
    }
};

#endif // SENSOR_H