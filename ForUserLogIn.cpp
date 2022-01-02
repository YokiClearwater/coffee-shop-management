#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string.h>
#include "userLog.h"
using namespace std;

main()
{
    // functions
    void displayAdminPanelMenu();

    coffee_list *menu;
    menu = makeCoffeeList();
    get_coffee_menu(menu);

    List *user;
    user = makeEmptyList();
    readToList(user);
    // displayList(user);
    int choice;
    do
    {
        cout << "1.Main Menu\n";
        cout << "2.Admin Panel\n";
        cout << "3.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            loginOrSignup();
            while (choice >= 1 && choice <= 2)
            {
                if (choice == 1)
                {
                    LogInUser(user, menu);
                }
                else if (choice == 2)
                {
                    signUp(user, menu);
                }
                choice = loginOrSignup();
            }
        }
        break;
        case 2:
        {
            int choice2;
            displayAdminPanelMenu();
            cin >> choice2;
            switch (choice2)
            {
                //hllo
            // create coffee
            case 1:
            {
            }
            break;
            // read coffee
            case 2:
            {
            }
            break;
            // edit coffee
            case 3:
            {
            }
            break;
            // delete coffee
            case 4:
            {
            }
            break;
            // best-seller
            case 5:
            {
            }
            break;
            // total cash
            case 6:
            {
            }
            break;
            case 7:
            {
                        }
            break;
            }
        }
        }
    } while (choice != 3);
}

void displayAdminPanelMenu()
{
    cout << "1.Create\n";
    cout << "2.Read\n";
    cout << "3.Edit\n";
    cout << "4.Delete\n";
    cout << "5.Best-Seller Coffee\n";
    cout << "6.Total Cash\n";
    cout << "7.Exit\n";
}