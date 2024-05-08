#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>

#include "Measurement.h"  // Make sure to include the Measurement header
using namespace std;

class Sensor {
private:
    string sensorID;
    double latitude;
    double longitude;
    vector<Measurement> measurements;  // Vector to store associated measurements

public:
    // Constructors
    Sensor();
    Sensor(const string& id, double lat, double lon);

    // Getter and setter for sensorID
    string getSensorID() const;
    void setSensorID(const string& id);

    // Getter and setter for latitude
    double getLatitude() const;
    void setLatitude(double lat);

    // Getter and setter for longitude
    double getLongitude() const;
    void setLongitude(double lon);

    // Methods to manage measurements
    void addMeasurement(const Measurement& measurement);
    vector<Measurement> getMeasurements() const;

    // Additional functionality as needed
};

#endif  // SENSOR_H
