#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Attribute.h"
#include "Date.h"
#include "Measurement.h"
#include "Sensor.h"
#include "SensorManagementServices.h"

void loadAttributes(const string& filename, vector<Attribute>& attributes);
void loadMeasurements(const string& filename, vector<Measurement>& measurements);

int main() {
    vector<Attribute> attributes;
    vector<Measurement> measurements;
    vector<Sensor> sensors;
    SensorManagementServices sensorManagementServices;

    loadAttributes("dataset/attributes.csv", attributes);
    loadMeasurements("dataset/measurements.csv", measurements);
    sensorManagementServices.loadSensors("dataset/sensors.csv", sensors);

    // Pour la démonstration, affichez les tailles des vecteurs chargés
    cout << "Loaded " << attributes.size() << " attributes." << endl;
    cout << "Loaded " << measurements.size() << " measurements." << endl;
    cout << "Loaded " << sensors.size() << " sensors." << endl;

    /*
    cout << "Attributes details:" << endl;
    for (const auto& attr : attributes) {
        cout << "Attribute ID: " << attr.getAttributeID() << ", Unit: " << attr.getUnit() << ", Description: " << attr.getDescription() << endl;
    }
    cout << "Measurements details:" << endl;
    for (const auto& measurement : measurements) {
        cout << "Timestamp: " << measurement.getDate() << ", Attribute ID: " << measurement.getAttributeID() << ", Value: " << measurement.getValue() << endl;
    }

    cout << "Sensors details:" << endl;
    for (const auto& sensor : sensors) {
        cout << "Sensor ID: " << sensor.getSensorID() << ", Latitude: " << sensor.getLatitude() << ", Longitude: " << sensor.getLongitude() << endl;
    }
    */

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

void loadMeasurements(const string& filename, vector<Measurement>& measurements) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string timestampStr, sensorID, attributeID, valueStr;
            double value;
            Date timestamp;  // Assurez-vous que votre classe Date peut parser les strings de date
            getline(ss, timestampStr, ';');
            getline(ss, sensorID, ';');
            getline(ss, attributeID, ';');
            getline(ss, valueStr, ';');
            value = stod(valueStr);
            timestamp = Date::parse(timestampStr);  // Implémentez cette méthode dans votre classe Date
            measurements.emplace_back(timestamp, attributeID, value);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}