#include "Date.h"

Date ::Date() {
    // Obtenir le temps actuel du système
    auto currentTime = std::chrono::system_clock::now();

    // Convertir le temps actuel en temps système (time_t)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);

    // Convertir le temps système en une structure tm contenant les informations sur la date et l'heure
    std::tm *currentDateTm = std::localtime(&currentTimeT);

    year = currentDateTm->tm_year + 1900;
    month = currentDateTm->tm_mon + 1;
    day = currentDateTm->tm_mday;
    hour = currentDateTm->tm_hour;
    minute = currentDateTm->tm_min;
    second = currentDateTm->tm_sec;
}

Date::Date(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second){};