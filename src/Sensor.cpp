#include "Sensor.h"

<<<<<<< HEAD
// Default constructor
Sensor::Sensor() : sensorID(""), latitude(0.0), longitude(0.0) {
=======
#include <chrono>
#include <vector>

// Default constructor
Sensor::Sensor() : sensorID(""), latitude(0.0), longitude(0.0) {
    // Initialize sensorID to an empty string and latitude and longitude to 0.0
>>>>>>> Saad
}

// Parameterized constructor
Sensor::Sensor(const std::string& id, double lat, double lon) : sensorID(id), latitude(lat), longitude(lon) {
<<<<<<< HEAD
=======
    // Initialize sensorID, latitude, and longitude with the provided values
>>>>>>> Saad
}

// Getter for sensorID
std::string Sensor::getSensorID() const {
<<<<<<< HEAD
    return sensorID;
=======
    return sensorID;  // Return the sensorID
>>>>>>> Saad
}

// Setter for sensorID
void Sensor::setSensorID(const std::string& id) {
<<<<<<< HEAD
    sensorID = id;
=======
    sensorID = id;  // Set the sensorID to the provided value
>>>>>>> Saad
}

// Getter for latitude
double Sensor::getLatitude() const {
<<<<<<< HEAD
    return latitude;
=======
    return latitude;  // Return the latitude
>>>>>>> Saad
}

// Setter for latitude
void Sensor::setLatitude(double lat) {
<<<<<<< HEAD
    latitude = lat;
=======
    latitude = lat;  // Set the latitude to the provided value
>>>>>>> Saad
}

// Getter for longitude
double Sensor::getLongitude() const {
<<<<<<< HEAD
    return longitude;
=======
    return longitude;  // Return the longitude
>>>>>>> Saad
}

// Setter for longitude
void Sensor::setLongitude(double lon) {
<<<<<<< HEAD
    longitude = lon;
=======
    longitude = lon;  // Set the longitude to the provided value
>>>>>>> Saad
}

// Method to add a measurement to the sensor
void Sensor::addMeasurement(const Measurement& measurement) {
<<<<<<< HEAD
    measurements.push_back(measurement);
=======
    measurements.push_back(measurement);  // Add the provided measurement to the measurements vector
>>>>>>> Saad
}

// Method to get all measurements
std::vector<Measurement> Sensor::getMeasurements() const {
<<<<<<< HEAD
    return measurements;
=======
    return measurements;  // Return the measurements vector
}

// Method to filter measurements by period
std::vector<Measurement> Sensor::getMeasurementsForPeriod(int days) const {
    std::vector<Measurement> filteredMeasurements;           // Vector to store the filtered measurements
    auto now = std::chrono::system_clock::now();             // Get the current time
    auto startPeriod = now - std::chrono::hours(24 * days);  // Calculate the start of the period

    // Loop through all measurements
    for (const auto& measurement : measurements) {
        auto measurementTime = std::chrono::system_clock::from_time_t(measurement.getDate().to_time_t());  // Convert the measurement date to time point
        // If the measurement time is within the period, add it to the filtered measurements
        if (measurementTime >= startPeriod && measurementTime <= now) {
            filteredMeasurements.push_back(measurement);
        }
    }

    return filteredMeasurements;  // Return the filtered measurements
>>>>>>> Saad
}

// Method to display sensor details
void Sensor::displayDetails() const {
<<<<<<< HEAD
=======
    // Print the sensor details
>>>>>>> Saad
    std::cout << "Sensor ID: " << sensorID << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Measurements:" << std::endl;
<<<<<<< HEAD
=======
    // Loop through all measurements and print their details
>>>>>>> Saad
    for (const Measurement& measurement : measurements) {
        std::cout << "  Date: " << measurement.getDate() << std::endl;
        std::cout << "  Attribute ID: " << measurement.getAttributeID() << std::endl;
        std::cout << "  Value: " << measurement.getValue() << std::endl;
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> Saad
