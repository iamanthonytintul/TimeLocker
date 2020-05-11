#ifndef TIMELOCKER_STRINGCREATOR_H
#define TIMELOCKER_STRINGCREATOR_H
#include <iostream>

const int SINGLE_NUMERAL = 1;
const int JANUARY = 1;
const int HOURS_IN_DAY = 24;
const int SECONDS_IN_MINUTE = 60;
const int MINUTES_IN_HOUR = 60;
const int START_YEAR = 1900;

const char KEY_START_SYMBOL = 'a';
const char KEY_END_SYMBOL = 'z';
const char PASSWORD_START_SYMBOL = 'A';
const char PASSWORD_END_SYMBOL = '~';

class StringCreator {
public:
    StringCreator(int keySize, int passwordSize);
    StringCreator(const StringCreator&) = delete;
    void operator=(const StringCreator&) = delete;
    ~StringCreator() = default;
    std::string createKey() const;
    std::string createPassword() const;
    std::string createDeletionDate(int amountOfDays) const;
private:
    int _keySize;
    int _passwordSize;
};

#endif //TIMELOCKER_STRINGCREATOR_H