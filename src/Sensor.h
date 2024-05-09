#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>

#include "Measurement.h"  // Make sure to include the Measurement header

class Sensor {
private:
    std::string sensorID;
    double latitude;
    double longitude;
    std::vector<Measurement> measurements;  // Vector to store associated measurements

public:
    // Constructors
    Sensor();
    Sensor(const std::string& id, double lat, double lon);

    // Getter and setter for sensorID
    std::string getSensorID() const;
    void setSensorID(const std::string& id);

    // Getter and setter for latitude
    double getLatitude() const;
    void setLatitude(double lat);

    // Getter and setter for longitude
    double getLongitude() const;
    void setLongitude(double lon);

    // Methods to manage measurements
    void addMeasurement(const Measurement& measurement);
    std::vector<Measurement> getMeasurements() const;

    void displayDetails() const;
};

#endif  // SENSOR_H
