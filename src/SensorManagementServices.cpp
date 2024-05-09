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

double SensorManagementServices::calculateMarginError(double concentration, double weightedConcentration) {
    return fabs(concentration - weightedConcentration) / weightedConcentration;
}

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
