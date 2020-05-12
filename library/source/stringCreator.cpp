#include <ctime>
#include <random>
#include "stringCreator.h"

StringCreator::StringCreator(int keySize, int passwordSize,
                             char keyStartSymbol, char keyEndSymbol,
                             char passwordStartSymbol, char passwordEndSymbol):
                             _keySize(keySize), _passwordSize(passwordSize),
                             _keyStartSymbol(keyStartSymbol), _keyEndSymbol(keyEndSymbol),
                             _passwordStartSymbol(passwordStartSymbol), _passwordEndSymbol(passwordEndSymbol) {
}

std::string StringCreator::createKey() const {
    std::string result;
    const char start = (_keyStartSymbol) ? _keyStartSymbol : DEFAULT_KEY_START_SYMBOL;
    const char end = (_keyEndSymbol) ? _keyEndSymbol : DEFAULT_KEY_END_SYMBOL;
    const int size = (_keySize > EMPTY) ? _keySize : DEFAULT_KEY_SIZE;
    std::random_device random;
    std::mt19937 randomizer(random());
    std::uniform_int_distribution<char> randomCharInRange(start, end);
    for (int i = 0; i < size; i++) {
        result.insert(result.end(), randomCharInRange(randomizer));
    }
    return result;
}

std::string StringCreator::createPassword() const {
    std::string result;
    const char start = (_passwordStartSymbol) ? _passwordStartSymbol : DEFAULT_PASSWORD_START_SYMBOL;
    const char end = (_passwordEndSymbol) ? _passwordEndSymbol : DEFAULT_PASSWORD_END_SYMBOL;
    const int size = (_passwordSize > EMPTY) ? _passwordSize : DEFAULT_PASSWORD_SIZE;
    std::random_device random;
    std::mt19937 randomizer(random());
    std::uniform_int_distribution<char> randomCharInRange(start, end);
    for (int i = 0; i < size; i++) {
        result.insert(result.end(), randomCharInRange(randomizer));
    }
    return result;
}

std::string StringCreator::createDeletionDate(int amountOfDays) {
    std::string result;
    time_t now = time(nullptr) + amountOfDays * SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    tm* localTime = localtime(&now);

    std::string year = std::to_string(START_YEAR_TM_STRUCT + localTime->tm_year);
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
