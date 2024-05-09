#include "Date.h"

#include <iomanip>
#include <sstream>

// Example implementation
Date Date::parse(std::string dateString) {
    tm tm = {};
    std::istringstream ss(dateString);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");  // Assuming this format for the date string
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date string: " + dateString);
    }
    return Date(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

Date::Date() {
    // Implement default constructor logic, possibly setting to current time or zeroing fields
}

Date::Date(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    // This constructor initializes the Date with specified values
}

std::ostream& operator<<(std::ostream& os, const Date& dt) {
    os << dt.year << '-' << dt.month << '-' << dt.day << ' ' << dt.hour << ':' << dt.minute << ':' << dt.second;
    return os;
}