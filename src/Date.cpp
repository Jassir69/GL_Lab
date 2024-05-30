/*
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
*/

#include "Date.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <tuple>

Date::Date() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

Date::Date(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {}

Date Date::parse(const std::string& dateString) {
    std::tm tm = {};
    std::istringstream ss(dateString);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date string: " + dateString);
    }
    return Date(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

time_t Date::to_time_t() const {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    return std::mktime(&tm);
}

Date Date::addDays(int days) const {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day + days;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    time_t t = std::mktime(&tm);
    std::tm* new_tm = std::localtime(&t);
    return Date(new_tm->tm_year + 1900, new_tm->tm_mon + 1, new_tm->tm_mday, new_tm->tm_hour, new_tm->tm_min, new_tm->tm_sec);
}

bool Date::operator>=(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) >= std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

bool Date::operator<=(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) <= std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

bool Date::operator==(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) == std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

std::ostream& operator<<(std::ostream& os, const Date& dt) {
    os << std::setw(4) << std::setfill('0') << dt.year << '-'
       << std::setw(2) << std::setfill('0') << dt.month << '-'
       << std::setw(2) << std::setfill('0') << dt.day << ' '
       << std::setw(2) << std::setfill('0') << dt.hour << ':'
       << std::setw(2) << std::setfill('0') << dt.minute << ':'
       << std::setw(2) << std::setfill('0') << dt.second;
    return os;
}
