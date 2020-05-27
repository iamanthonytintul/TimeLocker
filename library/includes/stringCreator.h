#ifndef TIMELOCKER_STRINGCREATOR_H
#define TIMELOCKER_STRINGCREATOR_H

#include <random>
#include <string>

class StringCreator {
public:
    StringCreator(int keySize, int passwordSize,
                  char keyStartSymbol, char keyEndSymbol,
                  char passwordStartSymbol, char passwordEndSymbol);
    StringCreator(const StringCreator&) = delete;
    void operator=(const StringCreator&) = delete;
    ~StringCreator();

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
    std::mt19937* _randomizer;
};

#endif //TIMELOCKER_STRINGCREATOR_H