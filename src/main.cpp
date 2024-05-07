// g++ -std=c++17 -o main main.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Sensor.h"
using namespace std;
#include <Cleaner.h>

/*struct Date
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct Attribute
{
    string id;
    string unit;
    string description;
};

struct Measurement
{
    Date timestamp;
    string sensorId;
    string attributeId;
    double value;
};

struct Sensor
{
    string id;
    double latitude;
    double longitude;
};

struct Cleaner
{
    string id;
    double latitude;
    double longitude;
    Date startDate;
    Date endDate;
};

struct Provider
{
    string id;
    string cleanerId;
};

struct User
{
    string id;
    string sensorId;
};*/

vector<Attribute> loadAttributes()
{
    vector<Attribute> attributes;

    ifstream file("dataset/attributes.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier attribut.csv" << endl;
        return attributes;
    }

    // Sauter la première ligne
    string line;
    getline(file, line);

    while (getline(file, line))
    {
        istringstream ss(line);
        string id, unit, description;
        getline(ss, id, ';');
        getline(ss, unit, ';');
        getline(ss, description, ';');
        Attribute attribute = {id, unit, description};
        attributes.push_back(attribute);
    }

    return attributes;
}

vector<Measurement> loadMeasurements()
{
    vector<Measurement> measurements;

    ifstream file("dataset/measurements.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier measurement.csv" << endl;
        return measurements;
    }

    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string timestampStr, sensorId, attributeId, valueStr;
        double value;
        getline(ss, timestampStr, ';');
        getline(ss, sensorId, ';');
        getline(ss, attributeId, ';');
        getline(ss, valueStr, ';');
        value = stod(valueStr);

        Date timestamp;
        sscanf(timestampStr.c_str(), "%d-%d-%d %d:%d:%d", &timestamp.year, &timestamp.month, &timestamp.day, &timestamp.hour, &timestamp.minute, &timestamp.second);

        Measurement measurement = {timestamp, sensorId, attributeId, value};
        measurements.push_back(measurement);
    }

    return measurements;
}

vector<Sensor> loadSensors()
{
    vector<Sensor> sensors;

    ifstream file("dataset/sensors.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier sensors.csv" << endl;
        return sensors;
    }

    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string id, latitude, longitude;
        double latitudeDouble, longitudeDouble;
        getline(ss, id, ';');
        getline(ss, latitude, ';');
        getline(ss, longitude, ';');
        latitudeDouble = stod(latitude);
        longitudeDouble = stod(longitude);
        // Sensor sensor = {id, latitudeDouble, longitudeDouble};
        Sensor sensor() sensors.push_back(sensor);
    }

    return sensors;
}

vector<Cleaner> loadCleaners()
{
    vector<Cleaner> cleaners;

    ifstream file("dataset/cleaners.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier cleaners.csv" << endl;
        return cleaners;
    }

    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string id, latitude, longitude, startDateStr, endDateStr;
        double latitudeDouble, longitudeDouble;
        Date startDate, endDate;
        getline(ss, id, ';');
        getline(ss, latitude, ';');
        getline(ss, longitude, ';');
        getline(ss, startDateStr, ';');
        getline(ss, endDateStr, ';');
        latitudeDouble = stod(latitude);
        longitudeDouble = stod(longitude);
        sscanf(startDateStr.c_str(), "%d-%d-%d %d:%d:%d", &startDate.year, &startDate.month, &startDate.day, &startDate.hour, &startDate.minute, &startDate.second);
        sscanf(endDateStr.c_str(), "%d-%d-%d %d:%d:%d", &endDate.year, &endDate.month, &endDate.day, &endDate.hour, &endDate.minute, &endDate.second);
        // Cleaner cleaner = {id, latitudeDouble, longitudeDouble, startDate, endDate};
        Cleaner cleaner(id, latitudeDouble, longitudeDouble, startDate, endDate);
        cleaners.push_back(cleaner);
    }

    return cleaners;
}

vector<Provider> loadProvider()
{
    vector<Provider> providers;

    ifstream file("dataset/providers.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier providers.csv" << endl;
        return providers;
    }

    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string id, cleanerId;
        getline(ss, id, ';');
        getline(ss, cleanerId, ';');
        Provider provider = {id, cleanerId};
        providers.push_back(provider);
    }

    return providers;
}

vector<User> loadUsers()
{
    vector<User> users;

    ifstream file("dataset/users.csv");
    if (!file.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier users.csv" << endl;
        return users;
    }

    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string id, sensorId;
        getline(ss, id, ';');
        getline(ss, sensorId, ';');
        User user = {id, sensorId};
        users.push_back(user);
    }

    return users;
}

int main()
{
    vector<Attribute> attributes = loadAttributes();
    vector<Measurement> measurements = loadMeasurements();
    vector<Sensor> sensors = loadSensors();
    vector<Cleaner> cleaners = loadCleaners();
    vector<Provider> providers = loadProvider();
    vector<User> users = loadUsers();
    return 0;
}
