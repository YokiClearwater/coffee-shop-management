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

    string welcome = "\t***** WELCOME TO COFFEE MANAGEMENT SYSTEM *****";
    clearScreen();
    cout<<"\n\t";
    int n = welcome.size();
    sleepTime(500);
    for(int ii = 0; ii < n; ii++)
    {
        cout << welcome[ii] << flush;
        sleepTime(70);
    }

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
        }
        else if(choice == 2) {
            signUp(ul);
        }
        choice = loginOrSignup();
    }

    return 0;
}
