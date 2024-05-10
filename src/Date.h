#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>

class Date {
private:
    int year, month, day, hour, minute, second;

public:
    Date(); // Default constructor
    Date(int y, int m, int d, int h, int min, int s); // Parameterized constructor
    static Date parse(const std::string& dateString); // Parses date from string
    time_t to_time_t() const; // Converts Date to time_t
    friend std::ostream& operator<<(std::ostream& os, const Date& dt); // Output stream overload
};

#endif // DATE_H
