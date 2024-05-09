#include "Sensor.h"

// Default constructor
Sensor::Sensor() : sensorID(""), latitude(0.0), longitude(0.0) {
}

// Parameterized constructor
Sensor::Sensor(const std::string& id, double lat, double lon) : sensorID(id), latitude(lat), longitude(lon) {
}

// Getter for sensorID
std::string Sensor::getSensorID() const {
    return sensorID;
}

// Setter for sensorID
void Sensor::setSensorID(const std::string& id) {
    sensorID = id;
}

// Getter for latitude
double Sensor::getLatitude() const {
    return latitude;
}

// Setter for latitude
void Sensor::setLatitude(double lat) {
    latitude = lat;
}

// Getter for longitude
double Sensor::getLongitude() const {
    return longitude;
}

// Setter for longitude
void Sensor::setLongitude(double lon) {
    longitude = lon;
}

// Method to add a measurement to the sensor
void Sensor::addMeasurement(const Measurement& measurement) {
    measurements.push_back(measurement);
}

// Method to get all measurements
std::vector<Measurement> Sensor::getMeasurements() const {
    return measurements;
}

// Method to display sensor details
void Sensor::displayDetails() const {
    std::cout << "Sensor ID: " << sensorID << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Measurements:" << std::endl;
    for (const Measurement& measurement : measurements) {
        std::cout << "  Date: " << measurement.getDate() << std::endl;
        std::cout << "  Attribute ID: " << measurement.getAttributeID() << std::endl;
        std::cout << "  Value: " << measurement.getValue() << std::endl;
    }
}
