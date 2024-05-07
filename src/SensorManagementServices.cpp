#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "SensorsManagementServices.h"

// Utility function to split strings based on a delimiter
static std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Constructor implementation
SensorsManagementServices::SensorsManagementServices() {
    loadSensors();  // Load sensors from data source
}

// Loads sensors from a persistent data source
void SensorsManagementServices::loadSensors() {
    std::ifstream file("sensors.csv");
    std::string line;

    while (getline(file, line)) {
        auto tokens = split(line, ';');
        if (tokens.size() >= 3) {
            std::string sensorId = tokens[0];
            double latitude = std::stod(tokens[1]);
            double longitude = std::stod(tokens[2]);
            sensors.push_back(Sensor(sensorId, latitude, longitude));
        }
    }
    file.close();
}
