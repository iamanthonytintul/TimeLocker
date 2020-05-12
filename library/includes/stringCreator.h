#ifndef TIMELOCKER_STRINGCREATOR_H
#define TIMELOCKER_STRINGCREATOR_H
#include <iostream>

const int EMPTY = 0;
const int SINGLE_NUMERAL = 1;
const int JANUARY = 1;
const int HOURS_IN_DAY = 24;
const int SECONDS_IN_MINUTE = 60;
const int MINUTES_IN_HOUR = 60;
const int START_YEAR_TM_STRUCT = 1900;

const int DEFAULT_KEY_SIZE = 32;
const int DEFAULT_PASSWORD_SIZE = 8;

const char DEFAULT_KEY_START_SYMBOL = 'a';
const char DEFAULT_KEY_END_SYMBOL = 'z';
const char DEFAULT_PASSWORD_START_SYMBOL = 'A';
const char DEFAULT_PASSWORD_END_SYMBOL = '~';

class StringCreator {
public:
    StringCreator(int keySize, int passwordSize,
                  char keyStartSymbol, char keyEndSymbol,
                  char passwordStartSymbol, char passwordEndSymbol);
    StringCreator(const StringCreator&) = delete;
    void operator=(const StringCreator&) = delete;
    ~StringCreator() = default;

    std::string createKey() const;
    std::string createPassword() const;
    static std::string createDeletionDate(int amountOfDays);
private:
    const int _keySize;
    const int _passwordSize;
    const char _keyStartSymbol;
    const char _keyEndSymbol;
    const char _passwordStartSymbol;
    const char _passwordEndSymbol;
};

#endif //TIMELOCKER_STRINGCREATOR_H