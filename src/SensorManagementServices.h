#if !defined(SENSORMANAGEMENTSERVICES_H)
#define SENSORMANAGEMENTSERVICES_H

using namespace std;
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
#include "Sensor.h"

class SensorManagementServices {
private:
    vector<Sensor> sensors;          // This will hold all sensor objects
    map<string, Sensor> sensorsMap;  // For quick lookup by SensorID

public:
    SensorManagementServices();  // Constructor to load sensors from data source

    vector<Sensor> getAllSensors() const;
    vector<Sensor> getAllPrivateIndividualSensors() const;
    vector<Sensor> getMalfunctioningSensors() const;
    void displaySensorData(const string& sensorId) const;
    double scoreSensor(const string& sensorId) const;
    void rankSensor() const;
    vector<Sensor> getTop10SimilarSensors(const string& sensorId) const;
    bool checkSensorReliability(const string& sensorId) const;

    // Utility functions for internal use
private:
    void loadSensors();  // Load sensors from a data source (e.g., CSV files)
    bool isSensorMalfunctioning(const Sensor& sensor) const;
};

#endif  // SENSORS_MANAGEMENT_SERVICES_H