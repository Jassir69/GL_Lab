#include "Attribute.h"

// Default constructor
Attribute::Attribute() : attributeID(""), unit(""), description("") {
}

// Parameterized constructor
Attribute::Attribute(const string& id, const string& unit, const string& description) : attributeID(id), unit(unit), description(description) {
}

// Getter for attributeID
string Attribute::getAttributeID() const {
    return attributeID;
}

// Setter for attributeID
void Attribute::setAttributeID(const string& id) {
    attributeID = id;
}

// Getter for unit
string Attribute::getUnit() const {
    return unit;
}

// Setter for unit
void Attribute::setUnit(const string& unit) {
    this->unit = unit;
}

// Getter for description
string Attribute::getDescription() const {
    return description;
}

// Setter for description
void Attribute::setDescription(const string& description) {
    this->description = description;
}
