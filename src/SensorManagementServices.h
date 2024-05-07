#if !defined(SENSORMANAGEMENTSERVICES_H)
#define SENSORMANAGEMENTSERVICES_H

using namespace std;
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "Sensor.h"

class SensorsManagementServices {
private:
    std::vector<Sensor> sensors;               // This will hold all sensor objects
    std::map<std::string, Sensor> sensorsMap;  // For quick lookup by SensorID

public:
    SensorsManagementServices();  // Constructor to load sensors from data source

    std::vector<Sensor> getAllSensors() const;
    std::vector<Sensor> getAllPrivateIndividualSensors() const;
    std::vector<Sensor> getMalfunctioningSensors() const;
    void displaySensorData(const std::string& sensorId) const;
    double scoreSensor(const std::string& sensorId) const;
    void rankSensor() const;
    std::vector<Sensor> getTop10SimilarSensors(const std::string& sensorId) const;
    bool checkSensorReliability(const std::string& sensorId) const;

    // Utility functions for internal use
private:
    void loadSensors();  // Load sensors from a data source (e.g., CSV files)
    bool isSensorMalfunctioning(const Sensor& sensor) const;
};

#endif  // SENSORS_MANAGEMENT_SERVICES_H
