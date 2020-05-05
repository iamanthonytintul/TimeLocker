#ifndef TIMELOCKER_STRINGCREATOR_H
#define TIMELOCKER_STRINGCREATOR_H
#include <iostream>

enum  { JANUARY = 1,
        HOURS_IN_DAY = 24,
        SECONDS_IN_MINUTE = 60,
        MINUTES_IN_HOUR = 60,
        START_YEAR = 1900
};

#define MAX_STRING_SIZE 40

#define KEY_START_SYMBOL 'a'
#define KEY_END_SYMBOL 'z'
#define PASSWORD_START_SYMBOL 'A'
#define PASSWORD_END_SYMBOL '~'

class StringCreator {
public:
    StringCreator();
    ~StringCreator() = default;
    std::string createKey();
    std::string createPassword();
    std::string createDeletionDate(int amountOfDays);
};

#endif //TIMELOCKER_STRINGCREATOR_H