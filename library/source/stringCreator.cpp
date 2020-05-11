#include <cstdlib>
#include <ctime>
#include "stringCreator.h"

StringCreator::StringCreator(int keySize, int passwordSize): _keySize(keySize), _passwordSize(passwordSize) {
    srand(time(NULL));
}

std::string StringCreator::createKey() const {
    std::string result;
    for (int i = 0; i < _keySize; i++) {
        result.insert(result.end(), char(KEY_START_SYMBOL + std::rand() %
                                           (KEY_END_SYMBOL - KEY_START_SYMBOL)));
    }
    return result;
}

std::string StringCreator::createPassword() const {
    std::string result;
    for (int i = 0; i < _passwordSize; i++) {
        result.insert(result.end(), char(PASSWORD_START_SYMBOL + std::rand() %
                                           (PASSWORD_END_SYMBOL - PASSWORD_START_SYMBOL)));
    }
    return result;
}

std::string StringCreator::createDeletionDate(int amountOfDays) const {
    std::string result;
    time_t now = time(NULL) + amountOfDays * SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    tm* localTime = localtime(&now);

    std::string year = std::to_string(START_YEAR + localTime->tm_year);
    std::string month = std::to_string(JANUARY + localTime->tm_mon);
    std::string day = std::to_string(localTime->tm_mday);

    result.append(year);
    result.insert(result.end(), '-');
    if (month.length() == SINGLE_NUMERAL) {
        result.insert(result.end(), '0');
    }
    result.append(month);
    result.insert(result.end(), '-');
    if (day.length() == SINGLE_NUMERAL) {
        result.insert(result.end(), '0');
    }
    result.append(day);

    return result;
}
