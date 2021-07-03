#ifdef _WIN32
  #include <Windows.h>
#else
  #include <termios.h>
#endif

static char get_choice()
{
  #ifdef _WIN32
    return toupper(getch());
  #else
    struct termios old, current;

    // getting terminal i/o settings
    tcgetattr(0, &old);

    // setting temporary settings same as normal ones
    current = old;

    // disabling the buffer and the visibility of entered key
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;

    // applying new i/o settings
    tcsetattr(0, TCSANOW, &current);

    // getting a character from user
    char ch;
    cin >> ch;

    // restoring previous i/o settings
    tcsetattr(0, TCSANOW, &old);

    // returning the uppercase character
    return toupper(ch);
  #endif
}

