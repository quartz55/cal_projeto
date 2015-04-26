#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>

#ifdef _WIN32
#include <stdlib.h>
#endif

class Input
{
private:

public:
    int getUnsignedInt(std::string Message);
    char getChar(std::string Message);
    std::string getString(std::string Message);
    void wait(std::string Message);
    void clear();
};

#endif

inline int Input::getUnsignedInt(std::string Message)
{
    int final = -1;
    do
    {
        std::cout << Message;
        std::cin >> final;
        std::cin.ignore(1000, '\n');
        if (std::cin.fail())
            std::cin.clear();
    }while(final < 0);

    return final;
}

inline char Input::getChar(std::string Message)
{
    char final = '0';
    std::cout << Message;
    std::cin >> final;
    std::cin.ignore(1000, '\n');
    if (std::cin.fail())
        std::cin.clear();

    return final;
}

inline std::string Input::getString(std::string Message)
{
    std::string final;
    do
    {
        std::cout << Message;
        getline(std::cin, final);
    }while(final.length() <= 0);

    return final;
}

inline void Input::wait(std::string Message)
{
    std::cout << Message;
    std::cin.get();
}

inline void Input::clear()
{
#ifdef _WIN32 // Windows: Console command (alternative: Windows API)
    system("cls");
#else // UNIX: ANSI escape codes
    std::cout << "\x1B[2J\x1B[H";
#endif
}
