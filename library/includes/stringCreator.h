#ifndef TIMELOCKER_STRINGCREATOR_H
#define TIMELOCKER_STRINGCREATOR_H
#include <iostream>

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

class StringCreator {
public:
    StringCreator();
    StringCreator(const StringCreator&) = delete;
    void operator=(const StringCreator&) = delete;
    ~StringCreator() = default;
    std::string createKey();
    std::string createPassword();
    std::string createDeletionDate(int amountOfDays);
};

#endif //TIMELOCKER_STRINGCREATOR_H