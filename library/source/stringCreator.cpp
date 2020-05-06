#include <cstdlib>
#include <ctime>
#include "includes/stringCreator.h"

StringCreator::StringCreator() {
    srand(time(NULL));
}

std::string StringCreator::createKey() {
    std::string result;
    for (int i = 0; i < MAX_STRING_SIZE; i++) {
        result.insert(result.end(), char(KEY_START_SYMBOL + std::rand() %
                                           (KEY_END_SYMBOL - KEY_START_SYMBOL)));
    }
    return result;
}

std::string StringCreator::createPassword() {
    std::string result;
    for (int i = 0; i < MAX_STRING_SIZE; i++) {
        result.insert(result.end(), char(PASSWORD_START_SYMBOL + std::rand() %
                                           (PASSWORD_END_SYMBOL - PASSWORD_START_SYMBOL)));
    }
    return result;
}

std::string StringCreator::createDeletionDate(int amountOfDays) {
    std::string result;
    time_t now = time(NULL) + amountOfDays * SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    tm* localTime = localtime(&now);

    std::string yearString = std::to_string(START_YEAR + localTime->tm_year);
    std::string monthString = std::to_string(JANUARY + localTime->tm_mon);
    std::string dayString = std::to_string(localTime->tm_mday);

    result.append(yearString);
    result.insert(result.end(), '-');
    if (monthString.length() == 1) {
        result.insert(result.end(), '0');
    }
    result.append(monthString);
    result.insert(result.end(), '-');
    if (dayString.length() == 1) {
        result.insert(result.end(), '0');
    }
    result.append(dayString);

    return result;
}
