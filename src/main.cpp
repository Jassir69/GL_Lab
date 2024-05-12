#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Attribute.h"
#include "Date.h"
#include "Measurement.h"
#include "Sensor.h"
#include "SensorManagementServices.h"

using namespace std;

void loadMeasurements(const string& filename, vector<Measurement>& measurements, unordered_map<string, Sensor>& sensors);
void loadAttributes(const string& filename, vector<Attribute>& attributes);
void loadSensors(const string& filename, unordered_map<string, Sensor>& sensors);

<<<<<<< HEAD
int main(int argc, char* argv[]) {
=======
int main() {
>>>>>>> Saad
    vector<Attribute> attributes;
    vector<Measurement> measurements;
    unordered_map<string, Sensor> sensors;

    loadAttributes("dataset/attributes.csv", attributes);
    loadMeasurements("dataset/measurements.csv", measurements, sensors);
    loadSensors("dataset/sensors.csv", sensors);

    cout << "Loaded " << attributes.size() << " attributes." << endl;
    cout << "Loaded " << measurements.size() << " measurements." << endl;
    cout << "Loaded " << sensors.size() << " sensors." << endl;

<<<<<<< HEAD
    string sensorID = argc > 1 ? argv[1] : "Sensor1";
    auto it = sensors.find(sensorID);
    if (it != sensors.end()) {
        bool isOperatingNormally = SensorManagementServices::checkSensorOperation(it->second, sensors, 7);
        assert(isOperatingNormally && "Sensor should be operating normally based on the mock data provided.");
        cout << "Test passed: " << sensorID << " is operating normally." << endl;
    } else {
        cerr << "Sensor with ID " << sensorID << " not found." << endl;
    }

=======
    // Test each sensor for operational status
    int faultyCount = 0;
    for (const auto& pair : sensors) {
        const string& sensorID = pair.first;
        const Sensor& sensor = pair.second;
        bool isOperatingNormally = SensorManagementServices::checkSensorOperation(sensor, sensors, 7);

        cout << "Sensor ID: " << sensorID << " - ";
        if (isOperatingNormally) {
            cout << "Operating normally." << endl;
        } else {
            cout << "Faulty." << endl;
            faultyCount++;
        }
    }

    cout << "Total faulty sensors: " << faultyCount << endl;
>>>>>>> Saad
    return 0;
}

void loadAttributes(const string& filename, vector<Attribute>& attributes) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string attributeID, unit, description;
            getline(ss, attributeID, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');
            attributes.emplace_back(attributeID, unit, description);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

void loadMeasurements(const string& filename, vector<Measurement>& measurements, unordered_map<string, Sensor>& sensors) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string timestampStr, sensorID, attributeID, valueStr;
            double value;
            Date timestamp;  // Ensure your Date class can parse the date strings
            getline(ss, timestampStr, ';');
            getline(ss, sensorID, ';');
            getline(ss, attributeID, ';');
            getline(ss, valueStr, ';');
            value = stod(valueStr);
            timestamp = Date::parse(timestampStr);  // Implement this method in your Date class

            Measurement newMeasurement(timestamp, attributeID, value);
            measurements.push_back(newMeasurement);  // Add to general measurement vector

            // Add the measurement to the corresponding sensor's vector
            if (sensors.find(sensorID) == sensors.end()) {
                sensors[sensorID] = Sensor(sensorID, 0.0, 0.0);  // Create a new sensor if it does not exist
            }
            sensors[sensorID].addMeasurement(newMeasurement);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

void loadSensors(const string& filename, unordered_map<string, Sensor>& sensors) {
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
            sensors.emplace(sensorID, Sensor(sensorID, latitude, longitude));
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}
