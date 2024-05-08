#include "Sensor.h"

#include <iostream>
#include <string>

Sensor::Sensor(const string &sensorId, double latitude, double longitude) : id(sensorId), latitude(latitude), longitude(longitude) {
}

void Sensor::addMeasurement(const string &attributeId, double value) {
    measurements[attributeId].push_back(value);
}

const map<string, vector<double>> &Sensor::getMeasurements() const {
    return measurements;
}