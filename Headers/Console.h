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
        usleep(ms*1000);
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

void loadingbar() {
    #ifdef _WIN32
        clearScreen();
        char a = 177, b = 219;
        cout << "\n\n\n\n";
        cout << "\n\n\n\n\t\t\t\t\t" << "Loading...\n\n";
        cout << "\t\t\t\t\t";
        for (int i = 0; i < 26; i++)
            cout << a;
        cout << "\r";
        cout << "\t\t\t\t\t";

        for (int i = 0; i < 26; i++) {
            cout << b;
            sleepTime(100);
        }
    #endif
    #ifdef __unix__
        float progress = 0.0;
        clearScreen();
        cout << "\n\n";
        while (progress < 1.0) {
            cout << "\t\t";
            int barWidth = 70;
            cout << "[";
            int pos = barWidth * progress;
            for (int i = 0; i < barWidth; ++i) {
                if (i < pos) cout << "=";
                else if (i == pos) cout << ">";
                else cout << " ";
            }
            sleepTime(70);
            cout << "] " << int(progress * 100.0) << " %\r";
            cout.flush();
            progress += 0.02; // for demonstration only
        }
    cout << endl;
    #endif
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

void delayPrint(string str) {
    clearScreen();
    cout<<"\n\t\t";
    int n = str.size();
    sleepTime(500);
    for(int i = 0; i < n; i++)
    {
        cout << str[i] << flush;
        sleepTime(70);
    }
    cout << "\n\n";
}

void helpUser() {
    ifstream file;
    file.open("README.md");
    string str;

    while(getline(file, str)) {
        cout << str << endl;
    }
    file.close();
}