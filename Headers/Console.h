#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

#ifdef _WIN32
#include <conio.h>
#endif
#ifdef __unix__
#include <unistd.h>
#endif

void clearScreen()
{
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

void sleepTime(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void loadingbar(void){

	for (int i=15;i<=100;i+=5){

		clearScreen();

		printf("\n\n\n\n\n\n\n\t\t\t\t");
		printf("%d %% Loading...\n\n\t\t",i);

		printf("");

		for (int j=0; j<i;j+=2){
			cout << " ";
		}
		sleepTime(100);
		if(i==90 || i==50 || i==96 || i==83){
			sleepTime(100);
		}

	}

}

void waitForInput() {
	do {
		std::cout << '\n' << "\t\tPress a key to continue...";
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