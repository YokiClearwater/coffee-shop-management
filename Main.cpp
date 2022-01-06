#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Headers/SHA256.h"
#include "Headers/Console.h"
#include "Headers/Login.h"
#include "Headers/Coffee.h"
#include "Headers/Sales.h"
#include "Headers/Menu.h"
using namespace std;

int main() {
    #ifdef _WIN32
        std::system("color 0A");
    #endif

    int choice;
    UserList *ul = readUserInfo("Data/UserInfo.txt");
    string welcome = "***** WELCOME TO COFFEE MANAGEMENT SYSTEM *****";
    delayPrint(welcome);

    loadingbar();

    do {
        choice = loginOrSignup();
    } while(choice < 1 || choice > 3);

    while(choice >= 1 && choice <= 2) {
        if(choice == 1) {
            UserInfo *U1 = logIn();
            if(U1) {
                cout << "Login Successfully!!" << endl;
                mainMenu(U1);
            }
            else {
                clearScreen();
                cout << "\n\t\tLogin Failed!!" << endl;
                cout << "\n\t\tPress ENTER to continue....";
                cin.get();
            }
        }
        else if(choice == 2) {
            signUp(ul);
        }
        choice = loginOrSignup();
    }

    return 0;
}
