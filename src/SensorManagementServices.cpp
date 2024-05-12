<<<<<<< HEAD
#include "SensorManagementServices.h"

std::vector<double> SensorManagementServices::calculateMeans(const Sensor& sensor, int period) {
    // Assume that Sensor class has a method to get measurements within a given period.
    // Return vector<double> {meanO3, meanSO2, meanNO2, meanPM10}
    return {};  // Placeholder implementation
}

std::vector<double> SensorManagementServices::calculateWeightedMeans(const Sensor& selectedSensor, const std::vector<Sensor>& nearbySensors, int period) {
    double weightTot = 0;
    std::vector<double> means = {0, 0, 0, 0};  // {O3, SO2, NO2, PM10}
    for (const auto& sensor : nearbySensors) {
        double weight = distance(selectedSensor, sensor);
        weightTot += weight;
        auto tempMeans = calculateMeans(sensor, period);
        for (size_t i = 0; i < means.size(); ++i) {
            means[i] += weight * tempMeans[i];
        }
    }
    if (weightTot > 0) {
        for (double& mean : means) {
            mean /= weightTot;
        }
    }
    return means;
}

double SensorManagementServices::distance(const Sensor& sensor1, const Sensor& sensor2) {
    // Implement the actual distance calculation, placeholder
    return sqrt(pow(sensor1.getLatitude() - sensor2.getLatitude(), 2) + pow(sensor1.getLongitude() - sensor2.getLongitude(), 2));
}

=======
#include "SensorManagementServices.h"  // Include the header file for SensorManagementServices class

// Function to check the operation of a sensor by comparing its measurements with those of the nearby sensors
double SensorManagementServices::checkSensorOperation(const Sensor &sensorSelected, const std::unordered_map<std::string, Sensor> &allSensors, int period) {
    auto means = calculateMeans(sensorSelected, period);  // Calculate the mean values for the selected sensor
    std::vector<Sensor> nearbySensors;                    // Create a vector to store the nearby sensors

    // Find the four closest sensors
    while (nearbySensors.size() < 4) {
        Sensor closest = closestSensor(sensorSelected, nearbySensors, allSensors);  // Find the closest sensor that is not already in the vector
        if (!closest.getSensorID().empty()) {                                       // If a valid sensor was found
            nearbySensors.push_back(closest);                                       // Add the sensor to the vector
        } else {
            break;  // If no valid sensor was found, break the loop
        }
    }

    auto weightedMeans = calculateWeightedMeans(sensorSelected, nearbySensors, period);  // Calculate the weighted mean values for the selected sensor and the nearby sensors
    std::vector<double> marginErrors;                                                    // Create a vector to store the margin of error for each pollutant

    // Loop over the mean values
    for (size_t i = 0; i < means.size(); i++) {
        marginErrors.push_back(calculateMarginError(means[i], weightedMeans[i]));  // Calculate the margin of error and add it to the vector
    }

    // Calculate the overall mean of the margin errors
    double sum = 0.0;
    for (const auto &error : marginErrors) {
        sum += error;
    }
    double overallMean = sum / marginErrors.size();

    return overallMean;  // Return the overall mean of the margin errors
}

// Function to calculate the mean values of the pollutants for a given sensor over a period
std::vector<double> SensorManagementServices::calculateMeans(const Sensor &sensor, int period) {
    auto measurements = sensor.getMeasurementsForPeriod(period);        // Get the measurements for the sensor over the period
    std::unordered_map<std::string, std::pair<double, int>> sumCounts;  // Create a map to store the sum and count of each pollutant

    // Loop over the measurements
    for (const auto &measurement : measurements) {
        const auto &id = measurement.getAttributeID();  // Get the attribute ID (pollutant type)
        sumCounts[id].first += measurement.getValue();  // Add the value to the sum for this pollutant
        sumCounts[id].second++;                         // Increment the count for this pollutant
    }

    std::vector<double> means;                                                 // Create a vector to store the mean values
    means.reserve(4);                                                          // Reserve space for 4 pollutants: O3, SO2, NO2, PM10
    const std::vector<std::string> pollutants = {"O3", "SO2", "NO2", "PM10"};  // Define the order of pollutants

    // Loop over the pollutants
    for (const auto &pollutant : pollutants) {
        if (sumCounts[pollutant].second > 0) {                                          // If there are measurements for this pollutant
            means.push_back(sumCounts[pollutant].first / sumCounts[pollutant].second);  // Calculate the mean and add it to the vector
        } else {
            means.push_back(0);  // If there are no measurements for this pollutant, add 0 to the vector
        }
    }

    return means;  // Return the vector of mean values
}

// Function to calculate the weighted mean values of the pollutants for a given sensor and its nearby sensors over a period
std::vector<double> SensorManagementServices::calculateWeightedMeans(const Sensor &selectedSensor, const std::vector<Sensor> &nearbySensors, int period) {
    double weightTotal = 0;                    // Initialize the total weight
    std::vector<double> means = {0, 0, 0, 0};  // Initialize the vector of mean values

    // Loop over the nearby sensors
    for (const auto &sensor : nearbySensors) {
        double weight = 1 / distance(selectedSensor, sensor);  // Calculate the weight for this sensor (inverse of the distance)
        weightTotal += weight;                                 // Add the weight to the total weight
        auto tempMeans = calculateMeans(sensor, period);       // Calculate the mean values for this sensor

        // Loop over the mean values
        for (size_t i = 0; i < means.size(); i++) {
            means[i] += tempMeans[i] * weight;  // Add the weighted mean to the corresponding value in the vector
        }
    }

    if (weightTotal > 0) {  // If the total weight is not 0
        for (double &mean : means) {
            mean /= weightTotal;  // Divide each mean value by the total weight to get the weighted mean
        }
    }
    return means;  // Return the vector of weighted mean values
}

// Function to calculate the Euclidean distance between two sensors
double SensorManagementServices::distance(const Sensor &sensor1, const Sensor &sensor2) {
    return sqrt(pow(sensor1.getLatitude() - sensor2.getLatitude(), 2) + pow(sensor1.getLongitude() - sensor2.getLongitude(), 2));
}

// Function to calculate the margin of error between the concentration and the weighted concentration
>>>>>>> Saad
double SensorManagementServices::calculateMarginError(double concentration, double weightedConcentration) {
    return fabs(concentration - weightedConcentration) / weightedConcentration;
}

<<<<<<< HEAD
bool SensorManagementServices::checkSensorOperation(const Sensor& sensorSelected, const std::unordered_map<std::string, Sensor>& allSensors, int period) {
    auto means = calculateMeans(sensorSelected, period);
    std::vector<Sensor> nearbySensors;

    // Find the five closest sensors, excluding the selected sensor
    for (int i = 0; i < 5; ++i) {
        Sensor closest = closestSensor(sensorSelected, nearbySensors, allSensors);
        if (closest.getSensorID() != sensorSelected.getSensorID()) {  // Make sure the closest is not the selected sensor itself
            nearbySensors.push_back(closest);
        }
    }

    auto weightedMeans = calculateWeightedMeans(sensorSelected, nearbySensors, period);
    std::vector<double> margins = {calculateMarginError(means[0], weightedMeans[0]), calculateMarginError(means[1], weightedMeans[1]), calculateMarginError(means[2], weightedMeans[2]),
                                   calculateMarginError(means[3], weightedMeans[3])};

    for (auto margin : margins) {
        if (margin > 0.1) {
            return false;  // Sensor is faulty
        }
    }
    return true;  // Sensor is operating normally
}

Sensor SensorManagementServices::closestSensor(const Sensor& sensorSelected, const std::vector<Sensor>& excludedSensors, const std::unordered_map<std::string, Sensor>& allSensors) {
    double dist = std::numeric_limits<double>::max();
    Sensor closest;
    for (const auto& pair : allSensors) {
        const auto& sensor = pair.second;
        // Make sure the sensor is not the selected sensor and not already in the excluded list
        if (sensor.getSensorID() != sensorSelected.getSensorID() &&
            std::find_if(excludedSensors.begin(), excludedSensors.end(), [&sensor](const Sensor& s) { return s.getSensorID() == sensor.getSensorID(); }) == excludedSensors.end()) {
            double currentDist = distance(sensorSelected, sensor);
            if (currentDist < dist) {
                dist = currentDist;
                closest = sensor;
            }
        }
    }
    return closest;
}
=======
// Function to find the closest sensor to a given sensor that is not already in a list of excluded sensors
Sensor SensorManagementServices::closestSensor(const Sensor &sensorSelected, const std::vector<Sensor> &excludedSensors, const std::unordered_map<std::string, Sensor> &allSensors) {
    double dist = std::numeric_limits<double>::max();  // Initialize the minimum distance to the maximum possible value
    Sensor closest;                                    // Initialize the closest sensor

    // Loop over all sensors
    for (const auto &pair : allSensors) {
        const auto &sensor = pair.second;  // Get the sensor

        // If the sensor is not the selected sensor and is not in the list of excluded sensors
        if (sensor.getSensorID() != sensorSelected.getSensorID() &&
            std::find_if(excludedSensors.begin(), excludedSensors.end(), [&sensor](const Sensor &s) { return s.getSensorID() == sensor.getSensorID(); }) == excludedSensors.end()) {
            double currentDist = distance(sensorSelected, sensor);  // Calculate the distance to the selected sensor
            if (currentDist < dist) {                               // If the distance is less than the current minimum distance
                dist = currentDist;                                 // Update the minimum distance
                closest = sensor;                                   // Update the closest sensor
            }
        }
    }
    return closest;  // Return the closest sensor
}
>>>>>>> Saad
