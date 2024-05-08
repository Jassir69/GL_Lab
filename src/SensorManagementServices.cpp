#include "SensorManagementServices.h"

#include <fstream>

// Constructor implementation
SensorManagementServices::SensorManagementServices() {
}

void SensorManagementServices::loadSensors(const string& filename, vector<Sensor>& sensors) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string sensorID;
            double latitude, longitude;
            getline(ss, sensorID, ';');
            ss >> latitude;
            ss.ignore();  // Ignore the semicolon
            ss >> longitude;
            sensors.emplace_back(sensorID, latitude, longitude);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}
