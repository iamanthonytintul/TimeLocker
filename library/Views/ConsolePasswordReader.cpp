#include "View.h"

std::string ConsolePasswordReader::readPassword(std::istream& input, std::ostream& output) {

    termios savedTerminal{};

    tcgetattr(STDIN_FILENO, &savedTerminal);
    termios newTerminal = savedTerminal;

    newTerminal.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTerminal);

    getline(input, password);

    output << std::endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &savedTerminal);

    return password;
}