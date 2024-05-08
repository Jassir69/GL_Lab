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
    SensorManagementServices();                                         // Constructor to load sensors from data source
    void loadSensors(const string& filename, vector<Sensor>& sensors);  // Load sensors from a data source (e.g., CSV files)

    // Utility functions for internal use
private:
};

#endif  // SENSORS_MANAGEMENT_SERVICES_H