#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

using namespace std;

#include <string>

class Attribute {
private:
    string attributeID;  // Identifiant unique pour le type de mesure
    string unit;         // Unité de mesure (par exemple, µg/m3)
    string description;  // Description du type de mesure

public:
    // Constructors
    Attribute();
    Attribute(const string& id, const string& unit, const string& description);

    // Getter for attributeID
    string getAttributeID() const;
    // Setter for attributeID
    void setAttributeID(const string& id);

    // Getter for unit
    string getUnit() const;
    // Setter for unit
    void setUnit(const string& unit);

    // Getter for description
    string getDescription() const;
    // Setter for description
    void setDescription(const string& description);
};

#endif  // ATTRIBUTE_H
