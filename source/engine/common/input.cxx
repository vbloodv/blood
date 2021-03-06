#include "../../../include/blood/common/input.hxx"                                   

#ifdef WIN32
#include <conio.h>
#endif

#ifdef UNIX
#include <termios.h>
#include <unistd.h>
#endif

#include <iostream>

std::string blood::fn::input::get_string()
{
    std::string result;
    std::getline(std::cin, result);
    return result;
}

int blood::fn::input::get_menu_number()
{
    const auto key_code = blood::fn::input::getch();
    const int key = (key_code)-48;

    return (key < 0 || 9 < key) ? -1 : key;
}

bool blood::fn::input::get_yes_no()
{
    const auto key_code = blood::fn::input::getch();
    return (key_code == 121 || key_code == 173) ? true : false; // Expression 'key_code == 173' is always false. The value range of char type -128, 127
}

int blood::fn::input::get_number()
{
    int result = 0;
    const std::string str = get_string();
    for (auto symbol : str)
    {
        const int val = convert_symbol_to_number(symbol);
        if (val != -1)
            result = result * 10 + val;
        else
            return -1;
    }
    return result;
}

int blood::fn::input::convert_symbol_to_number(char _symbol)
{
    const int key = (_symbol)-48;
    return (key < 0 || 9 < key) ? -1 : key;
}

void blood::fn::input::press_any_keys()
{
    get_yes_no();
}

char blood::fn::input::getch()
{
#if defined(WIN32) || defined(MSVS)
    return _getch();
#endif // end BLOOD_VS
#if defined(UNIX)
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
#endif // end BLOOD_UNIX
}
