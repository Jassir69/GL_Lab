
#if !defined(DATE_H)
#define DATE_H

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

class Date {
public:
    Date();
    Date(int year, int month, int day, int hour, int minute, int second);

protected:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

#endif