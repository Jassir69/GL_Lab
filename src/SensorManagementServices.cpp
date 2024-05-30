#include "SensorManagementServices.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>

#include "SensorManagementServices.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>

// Function to get attribute ID by index
std::string SensorManagementServices::getAttributeIDByIndex(size_t index)
{
    static const std::vector<std::string> attributeIDs = {"O3", "SO2", "NO2", "PM10"};
    return attributeIDs[index];
}

// Function to calculate the mean values of the pollutants for a given sensor over a period
std::vector<double> SensorManagementServices::calculateMeans(const Sensor &sensor, const Date &startDate, const Date &endDate)
{
    auto measurements = sensor.getMeasurementsForPeriod(startDate, endDate);
    std::unordered_map<std::string, std::pair<double, int>> sumCounts;

    // Loop over the measurements
    for (const auto &measurement : measurements)
    {
        const auto &id = measurement.getAttributeID();
        sumCounts[id].first += measurement.getValue();
        sumCounts[id].second++;
    }

    std::vector<double> means;
    means.reserve(4);
    const std::vector<std::string> pollutants = {"O3", "SO2", "NO2", "PM10"};

    for (const auto &pollutant : pollutants)
    {
        if (sumCounts[pollutant].second > 0)
        {
            means.push_back(sumCounts[pollutant].first / sumCounts[pollutant].second);
        }
        else
        {
            means.push_back(0);
        }
    }

    return means;
}

// Function to calculate the weighted mean values of the pollutants for a given sensor and its nearby sensors over a period
// The weight of a sensor is inversely proportional to the distance between the sensor and the selected sensor
std::vector<double> SensorManagementServices::calculateWeightedMeans(const Sensor &selectedSensor, const std::vector<Sensor> &nearbySensors, const Date &startDate, const Date &endDate)
{
    std::vector<double> totalWeightedValues(4, 0.0);
    std::vector<double> totalWeights(4, 0.0);

    for (const auto &sensor : nearbySensors)
    {
        double weight = 1.0 / distance(selectedSensor, sensor);
        auto tempMeans = calculateMeans(sensor, startDate, endDate);

        for (size_t i = 0; i < tempMeans.size(); i++)
        {
            totalWeightedValues[i] += tempMeans[i] * weight;
            totalWeights[i] += weight;
        }
    }

    std::vector<double> weightedMeans(4, 0.0);
    for (size_t i = 0; i < totalWeightedValues.size(); i++)
    {
        if (totalWeights[i] != 0)
        {
            weightedMeans[i] = totalWeightedValues[i] / totalWeights[i];
        }
    }

    return weightedMeans;
}

// Function to calculate the Euclidean distance between two sensors
double SensorManagementServices::distance(const Sensor &sensor1, const Sensor &sensor2)
{
    return sqrt(pow(sensor1.getLatitude() - sensor2.getLatitude(), 2) + pow(sensor1.getLongitude() - sensor2.getLongitude(), 2));
}

// Function to calculate the margin of error between the concentration and the weighted concentration
double SensorManagementServices::calculateMarginError(double concentration, double weightedConcentration)
{
    return fabs(concentration - weightedConcentration) / weightedConcentration;
}

// Function to check the operation of a sensor by comparing its measurements with those of the nearby sensors
double SensorManagementServices::checkSensorOperation(const Sensor &sensorSelected, const std::unordered_map<std::string, Sensor> &allSensors, const Date &startDate, const Date &endDate)
{
    auto means = calculateMeans(sensorSelected, startDate, endDate);
    std::vector<Sensor> nearbySensors;

    while (nearbySensors.size() < 4)
    {
        Sensor closest = closestSensor(sensorSelected, nearbySensors, allSensors);
        if (!closest.getSensorID().empty())
        {
            nearbySensors.push_back(closest);
        }
        else
        {
            break;
        }
    }

    auto weightedMeans = calculateWeightedMeans(sensorSelected, nearbySensors, startDate, endDate);
    std::vector<double> marginErrors;

    for (size_t i = 0; i < means.size(); i++)
    {
        marginErrors.push_back(calculateMarginError(means[i], weightedMeans[i]));
    }

    double sum = 0.0;
    for (const auto &error : marginErrors)
    {
        sum += error;
    }

    return sum / marginErrors.size();
}

// Function to find the closest sensor to a given sensor that is not already in a list of excluded sensors
Sensor SensorManagementServices::closestSensor(const Sensor &sensorSelected, const std::vector<Sensor> &excludedSensors, const std::unordered_map<std::string, Sensor> &allSensors)
{
    double dist = std::numeric_limits<double>::max();
    Sensor closest;

    for (const auto &pair : allSensors)
    {
        const auto &sensor = pair.second;

        if (sensor.getSensorID() != sensorSelected.getSensorID() &&
            std::find_if(excludedSensors.begin(), excludedSensors.end(), [&sensor](const Sensor &s)
                         { return s.getSensorID() == sensor.getSensorID(); }) == excludedSensors.end())
        {
            double currentDist = distance(sensorSelected, sensor);
            if (currentDist < dist)
            {
                dist = currentDist;
                closest = sensor;
            }
        }
    }

    return closest;
}

// Function to find 'count' nearby sensors
std::vector<Sensor> SensorManagementServices::findNearbySensors(const Sensor &sensor, const std::unordered_map<std::string, Sensor> &allSensors, int count)
{
    std::vector<Sensor> nearbySensors;
    std::vector<std::pair<double, Sensor>> distances;

    for (const auto &pair : allSensors)
    {
        if (pair.first != sensor.getSensorID())
        {
            double dist = distance(sensor, pair.second);
            distances.push_back(std::make_pair(dist, pair.second));
        }
    }

    std::sort(distances.begin(), distances.end(), [](const std::pair<double, Sensor> &a, const std::pair<double, Sensor> &b)
              { return a.first < b.first; });

    for (int i = 0; i < count && i < distances.size(); i++)
    {
        nearbySensors.push_back(distances[i].second);
    }

    return nearbySensors;
}
