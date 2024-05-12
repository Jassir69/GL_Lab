<<<<<<< HEAD

#if !defined(DATE_H)
#define DATE_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Date.h"

class Date {
public:
    static Date parse(std::string dateString);

    Date();
    Date(int year, int month, int day, int hour, int minute, int second);

    // Vous pourriez également vouloir ajouter des méthodes d'accès pour récupérer les composantes de la date.
    int getYear() const {
        return year;
    }
    int getMonth() const {
        return month;
    }
    int getDay() const {
        return day;
    }
    int getHour() const {
        return hour;
    }
    int getMinute() const {
        return minute;
    }
    int getSecond() const {
        return second;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& dt);

protected:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

#endif
=======
#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>

class Date {
private:
    int year, month, day, hour, minute, second;

public:
    Date();                                                             // Default constructor
    Date(int y, int m, int d, int h, int min, int s);                   // Parameterized constructor
    static Date parse(const std::string& dateString);                   // Parses date from string
    time_t to_time_t() const;                                           // Converts Date to time_t
    friend std::ostream& operator<<(std::ostream& os, const Date& dt);  // Output stream overload
};

#endif  // DATE_H
>>>>>>> Saad
