#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NameCreator.h"

const int MAX_STRING_SIZE = 40;

const int JANUARY = 1;
const int HOURS_IN_DAY = 24;
const int SECONDS_IN_MINUTE = 60;
const int MINUTES_IN_HOUR = 60;
const int START_YEAR = 1900;

const char KEY_START_SYMBOL = 'a';
const char KEY_END_SYMBOL = 'z';
const char PASSWORD_START_SYMBOL = 'A';
const char PASSWORD_END_SYMBOL = '~';


std::string UniqueNameMaker::createKey() {
    std::string result;
    for (int i = 0; i < MAX_STRING_SIZE; i++) {
        result.insert(result.end(), char(KEY_START_SYMBOL + std::rand() %
                                                            (KEY_END_SYMBOL - KEY_START_SYMBOL)));
    }
    return result;
}

std::string UniqueNameMaker::createPassword() {
    std::string result;
    for (int i = 0; i < MAX_STRING_SIZE; i++) {
        result.insert(result.end(), char(PASSWORD_START_SYMBOL + std::rand() %
                                                                 (PASSWORD_END_SYMBOL - PASSWORD_START_SYMBOL)));
    }
    return result;
}

std::string UniqueNameMaker::createDeletionDate(int amountOfDays){
    std::string result;
    time_t now = time(NULL) + amountOfDays * SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    tm* localTime = localtime(&now);

    std::string year = std::to_string(START_YEAR + localTime->tm_year);
    std::string month = std::to_string(JANUARY + localTime->tm_mon);
    std::string day = std::to_string(localTime->tm_mday);

    result.append(year);
    result.insert(result.end(), '-');
    if (month.length() == 1) {
        result.insert(result.end(), '0');
    }
    result.append(month);
    result.insert(result.end(), '-');
    if (day.length() == 1) {
        result.insert(result.end(), '0');
    }
    result.append(day);

    return result;
}