#if !defined(SENSORMANAGEMENTSERVICES_H)
#define SENSORMANAGEMENTSERVICES_H

#include <cmath>
#include <vector>

#include "Sensor.h"

class SensorManagementServices {
public:
    static std::vector<double> calculateMeans(const Sensor& sensor, int period);
    static Sensor closestSensor(const Sensor& sensorSelected, const std::vector<Sensor>& excludedSensors, const std::unordered_map<std::string, Sensor>& allSensors);
    static std::vector<double> calculateWeightedMeans(const Sensor& selectedSensor, const std::vector<Sensor>& nearbySensors, int period);
    static double distance(const Sensor& sensor1, const Sensor& sensor2);
    static double calculateMarginError(double concentration, double weightedConcentration);
    static bool checkSensorOperation(const Sensor& sensorSelected, const std::unordered_map<std::string, Sensor>& allSensors, int period);
};

#endif  // SENSORS_MANAGEMENT_SERVICES_H