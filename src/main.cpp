#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>


// Include necessary header files
#include "Attribute.h"
#include "Date.h"
#include "Measurement.h"
#include "Sensor.h"
#include "SensorManagementServices.h"

using namespace std;

// Function prototypes for loading data from CSV files
void loadAttributes(const std::string &filename, std::vector<Attribute> &attributes);
void loadMeasurements(const std::string &filename, std::vector<Measurement> &measurements, std::unordered_map<std::string, Sensor> &sensors);
void loadSensors(const std::string &filename, std::unordered_map<std::string, Sensor> &sensors);

// Function to analyze sensor data for Sensor
void analyzeSensor(const std::unordered_map<std::string, Sensor>& sensors, const Date& startDate, const Date& endDate);

int main() {
    std::vector<Attribute> attributes;
    std::vector<Measurement> measurements;
    std::unordered_map<std::string, Sensor> sensors;

    // Load data from CSV files
    loadAttributes("dataset/attributes.csv", attributes);
    loadSensors("dataset/sensors.csv", sensors);
    loadMeasurements("dataset/measurements.csv", measurements, sensors);

    // Get start and end dates from the user
    std::string start, end;
    start = "2019-01-01";
    end = "2019-12-31";
    //std::cout << "Enter start date (YYYY-MM-DD): ";
    //std::cin >> start;
    //std::cout << "Enter end date (YYYY-MM-DD): ";
    //std::cin >> end;
    
    Date startDate = Date::parse(start + " 00:00:00");
    Date endDate = Date::parse(end + " 23:59:59");

    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;

    // Analyze sensor data for Sensor
    analyzeSensor(sensors, startDate, endDate);

    return 0;
}

// Function to analyze sensor data
void analyzeSensor(const std::unordered_map<std::string, Sensor>& sensors, const Date& startDate, const Date& endDate) {
    string sensorID ;
    cout << "Enter the sensor ID to analyze: ";
    cin >> sensorID;
    auto sensorIt = sensors.find("Sensor" + sensorID);


    if (sensorIt != sensors.end()) {
        const Sensor& sensor = sensorIt->second;
        int deviationCount = 0;
        int totalCount = 0;

        //std::cout << "Coordinates: (" << sensor.getLatitude() << ", " << sensor.getLongitude() << ")\n"; //TRACE A NE PAS EFFACER !!!

        // Find nearby sensors
        std::vector<Sensor> nearbySensors = SensorManagementServices::findNearbySensors(sensor, sensors, 4);
        //std::cout << "Nearby Sensors:\n";
        //for (const auto& nearby : nearbySensors) {std::cout << nearby.getSensorID() << " at distance " << SensorManagementServices::distance(sensor, nearby) << std::endl;} //TRACE A NE PAS EFFACER !!!

        // Calculate deviations for each day in the period
        for (Date date = startDate; date <= endDate; date = date.addDays(1)) // Loop over each day in the period
            {
            std::vector<double> weightedMeans = SensorManagementServices::calculateWeightedMeans(sensor, nearbySensors, date, date.addDays(1));
            //SE PREPARER UNE STRUCT QUI POINTE DEJA SUR LES DATES DANS LE BON ORDRE
            for (const auto& measurement : sensor.getMeasurements()) // Loop over each measurement for the sensor
                {
                if (measurement.getDate().to_time_t() >= date.to_time_t() && measurement.getDate().to_time_t() < date.addDays(1).to_time_t()) // Check if the measurement is within the current day
                    {
                    double currentValue = measurement.getValue();
                    std::vector<double> weightedMeans = SensorManagementServices::calculateWeightedMeans(sensor, nearbySensors, date, date.addDays(1));

                    // Find the corresponding weighted mean for the attribute
                    double weightedMean = 0;

                    for (size_t i = 0; i < weightedMeans.size(); i++) // Loop over the weighted means
                    {
                        if (measurement.getAttributeID() == SensorManagementServices::getAttributeIDByIndex(i)) // Check if the attribute ID matches
                        {
                            weightedMean = weightedMeans[i];
                            //std::cout << date << ":" << measurement.getAttributeID() << " " << measurement.getValue() << " compared to " << weightedMean << std::endl ; //TRACE A NE PAS EFFACER !!!
                            break;
                        }
                    }

                    double marginError = SensorManagementServices::calculateMarginError(currentValue, weightedMean);
                    if (marginError > 0.2) {
                        //std::cout << "deviates" << std::endl ; //TRACE A NE PAS EFFACER !!!
                        deviationCount++;
                    }
                    totalCount++;
                    }
                    
                }
        }

        std::cout << "Total Measurements: " << totalCount << std::endl;
        std::cout << "Deviations: " << deviationCount << std::endl;

        double deviationRate = static_cast<double>(deviationCount) / totalCount;
        std::cout << "Deviation Rate for Sensor: " << deviationRate*100 << "%" << std::endl;
        std::cout << "Reliability: " << (deviationRate > 0.2 ? "Not Reliable" : "Reliable") << std::endl;
    } else {
        std::cout << "Sensor not found." << std::endl;
    }
}



// Function to load attributes from a CSV file
void loadAttributes(const string &filename, vector<Attribute> &attributes)
{
    // Open the file
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        // Read each line of the file
        while (getline(file, line))
        {
            // Use a stringstream to parse the line
            stringstream ss(line);
            string attributeID, unit, description;

            // Get the attribute ID, unit, and description from the line
            getline(ss, attributeID, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');

            // Add the attribute to the vector
            attributes.emplace_back(attributeID, unit, description);
        }

        // Close the file
        file.close();
    }
    else
    {
        // Print an error message if the file could not be opened
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load measurements from a CSV file
void loadMeasurements(const string &filename, vector<Measurement> &measurements, unordered_map<string, Sensor> &sensors)
{
    // Open the file
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        // Read each line of the file
        while (getline(file, line))
        {
            // Use a stringstream to parse the line
            stringstream ss(line);
            string timestampStr, sensorID, attributeID, valueStr;
            double value;
            Date timestamp; // Ensure your Date class can parse the date strings

            // Get the timestamp, sensor ID, attribute ID, and value from the line
            getline(ss, timestampStr, ';');
            getline(ss, sensorID, ';');
            getline(ss, attributeID, ';');
            getline(ss, valueStr, ';');

            // Convert the value to a double
            value = stod(valueStr);

            // Parse the timestamp
            timestamp = Date::parse(timestampStr); // Implement this method in your Date class

            // Create a new measurement
            Measurement newMeasurement(timestamp, attributeID, value);

            // Add the measurement to the vector
            measurements.push_back(newMeasurement); // Add to general measurement vector

            // Add the measurement to the corresponding sensor's vector
            if (sensors.find(sensorID) == sensors.end())
            {
                // Create a new sensor if it does not exist
                sensors[sensorID] = Sensor(sensorID, 0.0, 0.0); 
            }

            // Add the measurement to the sensor
            sensors[sensorID].addMeasurement(newMeasurement);
        }

        // Close the file
        file.close();
    }
    else
    {
        // Print an error message if the file could not be opened
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load sensors from a CSV file
void loadSensors(const string &filename, unordered_map<string, Sensor> &sensors)
{
    // Open the file
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        // Read each line of the file
        while (getline(file, line))
        {
            // Use a stringstream to parse the line
            stringstream ss(line);
            string sensorID;
            double latitude, longitude;

            // Get the sensor ID, latitude, and longitude from the line
            getline(ss, sensorID, ';');
            ss >> latitude;
            ss.ignore(); // Ignore the semicolon
            ss >> longitude;

            // Add the sensor to the map
            sensors.emplace(sensorID, Sensor(sensorID, latitude, longitude));
        }

        // Close the file
        file.close();
    }
    else
    {
        // Print an error message if the file could not be opened
        cerr << "Unable to open file: " + filename << endl;
    }
}