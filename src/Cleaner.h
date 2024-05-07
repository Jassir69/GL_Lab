// Cleaner.h
#ifndef CLEANER_H
#define CLEANER_H

using namespace std;
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Date.h"

class Cleaner
{
private:
    string id;
    double latitude;
    double longitude;
    Date startDate;
    Date endDate;

public:
    Cleaner(string id, double latitude, double longitude, Date startDate, Date endDate) : id(id), latitude(latitude), longitude(longitude), startDate(startDate), endDate(endDate)
    {
    }
};

#endif // CLEANER_H