// Cleaner.h
#ifndef CLEANER_H
#define CLEANER_H

using namespace std;
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Date.h"

class Cleaner {
public:
    Cleaner(string id, double latitude, double longitude, Date startDate, Date endDate);

protected:
    string id;
    double latitude;
    double longitude;
    Date startDate;
    Date endDate;
};

#endif  // CLEANER_H