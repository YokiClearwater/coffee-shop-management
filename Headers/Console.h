#include <cstdlib>
#include <typeinfo>
using namespace std;

#ifdef _WIN32
#include <conio.h>
#include "windows.h"
#endif
#ifdef __unix__
#include <unistd.h>
#endif

bool checkSpace(string);
string userNameInput();


void clearScreen()
{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

void sleepTime(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms)
    #endif
}

void waitForInput() {
	do {
		std::cout << '\n' << "\t\tPress ENTER to continue...";
		cin.get();
	} while (cin.get() != '\n');
}

void errorInputHandling(int *choice) {
	while (!(cin >> *choice)) {
		cin.clear();
		cout << "\t\tBad Entry!!! Input Again: ";
		while(cin.get() != '\n');
	}
}

#ifdef _WIN32
string getPassword()
{
    string password;
    int ch;

    while ( ( ch = getch() ) != '\r' ) {
        if ( ch == '\b' ) {
            if ( password.size() > 0 ) {
                password.erase(password.size() - 1, 1 );
                cout<< "\b \b";
            }
        }
        else {
            password.push_back( ch );
            cout << "*";
        }
    }

    cout << "\n";

    return password;
}
#endif

void inputPass(string *password, const char *prompt) {
    #ifdef _WIN32
    cout << prompt;
    *password = getPassword();
    #endif

    #ifdef __unix__
    *password = getpass(prompt);
    #endif
}

bool checkSpace(string str) {
    for(int i = 0; i < str.size(); i++) {
        if(isspace(str[i])) {
            return true;
            break;
        }
    }
    return false;
}

void loadingbar()
{
    clearScreen();
    // Initialize char for printing
    // loading bar
    char a = 177, b = 219;

    cout << "\n\n\n\n";
    cout << "\n\n\n\n\t\t\t\t\t" << "Loading...\n\n";
    cout << "\t\t\t\t\t";

    // Print initial loading bar
    for (int i = 0; i < 26; i++)
        cout << a;

    // Set the cursor again starting
    // point of loading bar
    cout << "\r";
    cout << "\t\t\t\t\t";

    // Print loading bar progress
    for (int i = 0; i < 26; i++) {
        cout << b;

        // Sleep
        sleepTime(100);
    }
}

string userNameInput() {
    string name;
    getline(cin, name);
    while(checkSpace(name)) {
        cout << "\t\tUsername cannot contain space." << endl;
        cout << "\t\tEnter again: ";
        getline(cin, name);
    }
    return name;
}
