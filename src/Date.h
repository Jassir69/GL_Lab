
#if !defined(DATE_H)
#define DATE_H
using namespace std;
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Date.h"

class Date {
public:
    static Date parse(const string& dateString);

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

    friend ostream& operator<<(ostream& os, const Date& dt);

protected:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

#endif