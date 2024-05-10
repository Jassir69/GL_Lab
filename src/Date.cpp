#include "Date.h" 
#include <iomanip> 
#include <sstream> 
#include <stdexcept> 

// Default constructor initializes to current system time
Date::Date() {
    std::time_t now = std::time(0); // Get the current system time
    std::tm* now_tm = std::localtime(&now); // Convert the time_t object to a tm object
    // Initialize the Date object with the current date and time
    year = now_tm->tm_year + 1900;
    month = now_tm->tm_mon + 1;
    day = now_tm->tm_mday;
    hour = now_tm->tm_hour;
    minute = now_tm->tm_min;
    second = now_tm->tm_sec;
}

// Constructor with initialization
Date::Date(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {
    // Initialize the Date object with the provided date and time
}

// Parses date from string
Date Date::parse(const std::string& timestampStr) {
    std::istringstream ss(timestampStr); // Create a string stream from the input string
    std::string token; // String to hold each part of the date and time
    Date date; // Date object to hold the parsed date and time

    // Parse the year, month, day, hour, minute, and second from the string
    std::getline(ss, token, '-');
    date.year = std::stoi(token);
    std::getline(ss, token, '-');
    date.month = std::stoi(token);
    std::getline(ss, token, ' ');
    date.day = std::stoi(token);
    std::getline(ss, token, ':');
    date.hour = std::stoi(token);
    std::getline(ss, token, ':');
    date.minute = std::stoi(token);
    std::getline(ss, token, ';');
    date.second = std::stoi(token);

    return date; // Return the parsed date
}

// Converts Date to time_t
time_t Date::to_time_t() const {
    std::tm tm = {}; // Create a tm object
    // Set the tm object's fields to the Date object's fields
    tm.tm_year = year - 1900;  // tm_year is years since 1900
    tm.tm_mon = month - 1;     // tm_mon is 0-11
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    tm.tm_isdst = -1;          // Disable daylight saving time adjustment
    return mktime(&tm); // Convert the tm object to a time_t object and return it
}

// Output stream overload
std::ostream& operator<<(std::ostream& os, const Date& dt) {
    // Output the date and time in the format "YYYY-MM-DD HH:MM:SS"
    os << dt.year << '-' << std::setfill('0') << std::setw(2) << dt.month << '-'
       << std::setw(2) << dt.day << ' ' << std::setw(2) << dt.hour << ':'
       << std::setw(2) << dt.minute << ':' << std::setw(2) << dt.second;
    return os; // Return the output stream
}