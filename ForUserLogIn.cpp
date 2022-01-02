#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include <Windows.h>
#include<fstream>
#include <string.h>
#include"userLog.h"
using namespace std;

main()
{
    coffee_list *menu;
    menu = makeCoffeeList();
    get_coffee_menu(menu);

    List *user;
    user = makeEmptyList();
    readToList(user);
    //displayList(user);
    int choice;
    do
    {
        choice=loginOrSignup();
    }while(choice<1 || choice>3);

    while(choice>=1 && choice <=2)
    {
        if(choice==1)
        {
            LogInUser(user, menu);
        }
        else if(choice==2)
        {
            signUp(user, menu);
        }
        choice=loginOrSignup();
    }


}
