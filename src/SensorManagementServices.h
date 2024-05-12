#if !defined(SENSORMANAGEMENTSERVICES_H)
#define SENSORMANAGEMENTSERVICES_H

#include <cmath>
<<<<<<< HEAD
=======
#include <unordered_map>
>>>>>>> Saad
#include <vector>

#include "Sensor.h"

<<<<<<< HEAD
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
=======
// Declare the SensorManagementServices class
class SensorManagementServices {
public:
    static std::vector<double> calculateMeans(const Sensor &sensor, int period);  // Declare a static function to calculate the mean values of the pollutants for a given sensor over a period
    static std::vector<double> calculateWeightedMeans(
        const Sensor &selectedSensor, const std::vector<Sensor> &nearbySensors,
        int period);  // Declare a static function to calculate the weighted mean values of the pollutants for a given sensor and its nearby sensors over a period

    static double distance(const Sensor &sensor1, const Sensor &sensor2);  // Declare a static function to calculate the Euclidean distance between two sensors

    static Sensor closestSensor(const Sensor &sensorSelected, const std::vector<Sensor> &excludedSensors, const std::unordered_map<std::string, Sensor> &allSensors);

    static double calculateMarginError(double concentration,
                                       double weightedConcentration);  // Declare a static function to calculate the margin of error between the concentration and the weighted concentration
    static double checkSensorOperation(const Sensor &sensorSelected, const std::unordered_map<std::string, Sensor> &allSensors,
                                       int period);  // Declare a static function to check the operation of a sensor by comparing its measurements with those of the nearby sensors // Declare a static
                                                     // function to check the operation of a sensor by comparing its measurements with those of the nearby sensors
};

#endif
>>>>>>> Saad
