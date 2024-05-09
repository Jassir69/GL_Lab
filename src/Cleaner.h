// Cleaner.h
#ifndef CLEANER_H
#define CLEANER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Date.h"

class Cleaner {
public:
    Cleaner(std::string id, double latitude, double longitude, Date startDate, Date endDate);

protected:
    std::string id;
    double latitude;
    double longitude;
    Date startDate;
    Date endDate;
};

#endif  // CLEANER_H