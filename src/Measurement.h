#ifndef MEASUREMENT_H
#define MEASUREMENT_H
using namespace std;
#include <string>

#include "Date.h"  // Include the Date class header

class Measurement {
private:
    Date date;           // Use Date class for the measurement's date
    string attributeID;  // ID for the type of measurement (e.g., O3 for ozone)
    double value;        // Numeric value of the measurement

public:
    // Constructors
    Measurement();
    Measurement(const Date& dt, const string& attrID, double val);

    // Getter for date
    Date getDate() const;
    // Setter for date
    void setDate(const Date& dt);

    // Getter for attribute ID
    string getAttributeID() const;
    // Setter for attribute ID
    void setAttributeID(const string& attrID);

    // Getter for value
    double getValue() const;
    // Setter for value
    void setValue(double val);
};

#endif  // MEASUREMENT_H
