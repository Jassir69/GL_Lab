// Include necessary libraries
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Include necessary header files
#include "Attribute.h"
#include "Date.h"
#include "Measurement.h"
#include "Sensor.h"
#include "SensorManagementServices.h"

// Use the standard namespace to avoid prefixing standard library functions with std::
using namespace std;

// Function prototypes for loading data from CSV files
void loadAttributes(const string &filename, vector<Attribute> &attributes);
void loadMeasurements(const string &filename, vector<Measurement> &measurements, unordered_map<string, Sensor> &sensors);
void loadSensors(const string &filename, unordered_map<string, Sensor> &sensors);

// Main function

/*
int main()
{
    // Create containers to hold attributes, measurements, and sensors
    vector<Attribute> attributes;
    vector<Measurement> measurements;
    unordered_map<string, Sensor> sensors;

    // Variables to count the number of reliable and unreliable sensors
    int reliableSensors = 0;
    int unreliableSensors = 0;

    // Load data from CSV files
    loadAttributes("dataset/attributes.csv", attributes);
    loadSensors("dataset/sensors.csv", sensors); // Load sensors before measurements
    loadMeasurements("dataset/measurements.csv", measurements, sensors);

    // Print the number of loaded attributes, measurements, and sensors
    cout << "Loaded " << attributes.size() << " attributes." << endl;
    cout << "Loaded " << measurements.size() << " measurements." << endl;
    cout << "Loaded " << sensors.size() << " sensors." << endl;

    // Sensor ID prefix
    string sensorID = "Sensor"; // Focusing only on Sensor1

    // Loop over the first 100 sensors
    for (int i = 0; i < 100; i++)
    {
        // Generate sensor ID
        sensorID = "Sensor" + to_string(i);

        // Print sensor's coordinates
        cout << "Longitudinal and Latitudinal coordinates for " << sensorID << ": ";
        cout << sensors[sensorID].getLatitude() << ", " << sensors[sensorID].getLongitude() << endl;

        // Find Sensor in the map
        auto it = sensors.find(sensorID);
        if (it != sensors.end())
        {
            // Get a reference to the sensor
            Sensor &sensor = it->second;
            vector<Sensor> nearbySensors;

            // Finding up to 5 nearest sensors
            for (int i = 0; i < 2; ++i)
            {
                // Find the closest sensor that is not already in nearbySensors
                Sensor closest = SensorManagementServices::closestSensor(sensor, nearbySensors, sensors);
                if (!closest.getSensorID().empty())
                {
                    // Print the ID and distance of the closest sensor
                    cout << "Closest sensor to " << sensorID << " is " << closest.getSensorID() << endl;
                    cout << "Distance: " << SensorManagementServices::distance(sensor, closest) << endl;

                    // Add the closest sensor to nearbySensors
                    nearbySensors.push_back(closest);
                }
            }

            // Calculate means for Sensor
            auto means = SensorManagementServices::calculateMeans(sensor, 3650);

            // Print the means for the sensor
            cout << "Means for " << sensorID << ": ";
            for (auto mean : means)
            {
                cout << mean << " ";
            }
            cout << endl;

            // Calculate and print means for nearby sensors
            for (auto &nearbySensor : nearbySensors)
            {
                auto nearbyMeans = SensorManagementServices::calculateMeans(nearbySensor, 3650);
                cout << "Means for " << nearbySensor.getSensorID() << ": ";
                for (auto mean : nearbyMeans)
                {
                    cout << mean << " ";
                }
                cout << endl;
            }

            // Calculate weighted means using nearby sensors
            auto weightedMeans = SensorManagementServices::calculateWeightedMeans(sensor, nearbySensors, 3650);

            // Calculate marginal errors
            cout << "Marginal Errors for " << sensorID << ": ";
            vector<double> marginErrors;
            for (size_t i = 0; i < means.size(); ++i)
            {
                double marginError = SensorManagementServices::calculateMarginError(means[i], weightedMeans[i]);
                marginErrors.push_back(marginError);
                cout << marginError << " ";
            }
            cout << endl;

            // Assess reliability
            bool isReliable = true;
            for (auto marginError : marginErrors)
            {
                // If any marginal error is greater than 0.2, the sensor is not reliable
                if (marginError > 0.2)
                { // Using a simple threshold for example
                    isReliable = false;
                    break;
                }
            }

            // Increment the count of reliable or unreliable sensors
            if (isReliable)
            {
                reliableSensors++;
            }
            else
            {
                unreliableSensors++;
            }

            // Print the reliability of the sensor
            cout << "Reliability: " << (isReliable ? "Reliable" : "Not Reliable") << endl;
        }
        else
        {
            // Print a message if the sensor was not found
            cout << "Sensor with ID " << sensorID << " not found." << endl;
        }
    }

    // Print the number of reliable and unreliable sensors
    cout << "Number of reliable sensors: " << reliableSensors << endl;
    cout << "Number of unreliable sensors: " << unreliableSensors << endl;

    return 0;
}
*/

int main()
{
    // Create containers to hold attributes, measurements, and sensors
    vector<Attribute> attributes;
    vector<Measurement> measurements;
    unordered_map<string, Sensor> sensors;

    // Variables to count the number of reliable and unreliable sensors
    int reliableSensors = 0;
    int unreliableSensors = 0;

    // Load data from CSV files
    loadAttributes("dataset/attributes.csv", attributes);
    loadSensors("dataset/sensors.csv", sensors); // Load sensors before measurements
    loadMeasurements("dataset/measurements.csv", measurements, sensors);

    // Print the number of loaded attributes, measurements, and sensors
    cout << "Loaded " << attributes.size() << " attributes." << endl;
    cout << "Loaded " << measurements.size() << " measurements." << endl;
    cout << "Loaded " << sensors.size() << " sensors." << endl;

    // Sensor ID prefix
    string sensorID = "Sensor"; // Focusing only on Sensor1

    // Loop over the first 100 sensors
    for (int i = 0; i < 100; i++)
    {
        // Generate sensor ID
        string sensorID = "Sensor" + to_string(i);

        // Print sensor's coordinates
        cout << "Longitudinal and Latitudinal coordinates for " << sensorID << ": ";
        cout << sensors[sensorID].getLatitude() << ", " << sensors[sensorID].getLongitude() << endl;

        // Find Sensor in the map
        auto it = sensors.find(sensorID);
        if (it != sensors.end())
        {
            // Get a reference to the sensor
            Sensor &sensor = it->second;

            // Calculate the mean values for the sensor
            vector<double> means = SensorManagementServices::calculateMeans(sensor, 3650); // Calculate means over 10 years == 3650 days
            cout << "Means for " << sensorID << ": ";
            for (auto mean : means)
            {
                cout << mean << " ";
            }
            cout << endl;

            // Find the closest sensors
            vector<Sensor> nearbySensors;
            for (int i = 0; i < 4; ++i)
            {
                // Find the closest sensor that is not already in nearbySensors
                Sensor closest = SensorManagementServices::closestSensor(sensor, nearbySensors, sensors);
                if (!closest.getSensorID().empty())
                {
                    // Print the ID and distance of the closest sensor
                    cout << "Closest sensor to " << sensorID << " is " << closest.getSensorID() << endl;
                    cout << "Distance: " << SensorManagementServices::distance(sensor, closest) << endl;

                    // Add the closest sensor to nearbySensors
                    nearbySensors.push_back(closest);
                }
            }

            // Calculate the weighted mean values for the sensor
            vector<double> weightedMeans = SensorManagementServices::calculateWeightedMeans(sensor, nearbySensors, 3650); // Calculate weighted means over 10 years == 3650 days
            cout << "Weighted means for " << sensorID << ": ";
            for (auto weightedMean : weightedMeans)
            {
                cout << weightedMean << " ";
            }
            cout << endl;

            // Calculate the marginal errors
            vector<double> marginErrors;
            cout << "Marginal Errors for " << sensorID << ": ";
            for (size_t i = 0; i < means.size(); ++i)
            {
                double marginError = SensorManagementServices::calculateMarginError(means[i], weightedMeans[i]);
                marginErrors.push_back(marginError);
                cout << marginError << " ";
            }
            cout << endl;

            // Check the operation of the sensor
            double overallMeanMarginError = SensorManagementServices::checkSensorOperation(sensor, sensors, 3650); // Check operation over 10 years == 3650 days 

            // Print the overall mean margin error
            cout << "Overall mean margin error for " << sensorID << ": " << overallMeanMarginError << endl;

            // Assess reliability
            bool isReliable = overallMeanMarginError <= 0.15; // Considering 15% margin error as reliable

            // Increment the count of reliable or unreliable sensors
            if (isReliable)
            {
                reliableSensors++;
            }
            else
            {
                unreliableSensors++;
            }

            // Print the reliability of the sensor
            cout << "Reliability: " << (isReliable ? "Reliable" : "Not Reliable") << endl;
        }
        else
        {
            // Print a message if the sensor was not found
            cout << "Sensor with ID " << sensorID << " not found." << endl;
        }
    }

    // Print the number of reliable and unreliable sensors
    cout << "Number of reliable sensors: " << reliableSensors << endl;
    cout << "Number of unreliable sensors: " << unreliableSensors << endl;

    return 0;
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