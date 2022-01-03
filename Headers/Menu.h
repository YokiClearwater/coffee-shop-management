#include <vector>

void mainMenu();
void buyCoffee(UserInfo *ul);
void adminPanel();

void mainMenu(UserInfo *ul) {
    int choice;
    clearScreen();
    cout<<"\n\t";
    
    cout << "***** Main Menu *****" << endl;
    
    sleepTime(200);
    cout<<"\n\t\t1. Ordering Coffee\n\t\t2. Admin Panel\n\t\t3. Back\n\n";
    sleepTime(200);
    do {
        cout<<"\t\tEnter Choice (1 - 3):  ";
        cin >> choice;

        if(choice == 1) {
            buyCoffee(ul);
            sleepTime(1000);
            clearScreen();
            mainMenu(ul);
        }
        else if(choice == 2) {
            adminPanel();
            clearScreen();
            mainMenu(ul);
        }

    }   while(choice < 1 || choice > 3);
    
}

void buyCoffee(UserInfo *ul) {
    coffeeList *menu = new coffeeList();
    int anotherdrink;
    vector<int> qBuy; // quantity Bought
    vector<float> coffeePrice; 
    float invoicePrice = 0;
    vector<string> coffeeName;
    readCoffeeList(menu);

    clearScreen();
    sleepTime(700);
    string username, coffeeID;
    username = ul->userName;
    int quantity, ff;
    float price;

    while(true){
        displayCoffeeList(menu);
        cout<<"\t\t\t\tEnter drink ID to order: "; cin>>coffeeID;
        coffeeElement *item = searchItem(menu, coffeeID);
        
        while(item == NULL) {
            cout << "ID Not Found!! Enter Again: ";
            cin >> coffeeID;
            item = searchItem(menu, coffeeID);
        }

        cout<<"\t\t\t\tQuantity: "; cin >> quantity;

        while(quantity <= 0)
        {
            cout<<"\n\t\t\tQuantity must be greater than zero. You can cancel order after input the quantity.\n";
            cout<<"\t\t\t\tQuantity: "; cin >> quantity;
        }

        cout<<"\t\t\t\tPrice to pay: "<< (item->price)*quantity <<" $\n";
        cout<<"\tPress 1 to confirm or press 2 to cancel order: "; cin>>ff;
        sleepTime(500);
        clearScreen();

        if(ff == 1) {
            coffeeName.push_back(item->name);
            coffeePrice.push_back(item->price*quantity);
            qBuy.push_back(quantity);
            //cout<<"\n\t\t#### Thank you for ordering our drinks ####\n";
            fstream f3;
            f3.open("Data/SaleHistory.txt", ios::app);
            f3 << username << "\t" << coffeeID << "\t" << quantity << "\t" << quantity*(item->price) <<"\n";
            f3.close();
        }
        item = menu->head;
        cout<<"\n\tType 1 to make another order or other number to finish order: ";
        cin>>anotherdrink;

        if(anotherdrink == 1) {
            continue;
        }
        else {
            sleepTime(500);
            clearScreen();
            if(qBuy.size() == 0) {break;}
            cout<<"\n\t\tWe are printing our invoice";
            for(int ii=1; ii <= 10; ii++)
            {
                cout<<". ";
                sleepTime(300);
            }
            cout<<"\n\n\t\t  "<<"Drink(s)"<<setw(19)<<"Quantity"<<setw(19)<<"Price($)\n";
            cout<<"\t\t----------------------------------------------\n";
            for(int kkk = 0; kkk < qBuy.size(); kkk++)
            {
                invoicePrice=invoicePrice+coffeePrice[kkk];
                cout<<"\t\t "<<setw(10)<<coffeeName[kkk]<<setw(15)<<qBuy[kkk]<<setw(16)<<coffeePrice[kkk]<<"\n";
            }
            cout<<"\t\t----------------------------------------------\n";
            cout<<"\t\t\tOverall price to pay is $" << invoicePrice <<"\n";
            cout<<"\n\t\t#### Thank you for ordering our drinks ####\n";
            int cc; cout <<"\t\t\tPress any number to go back to costumer panel: "; cin>>cc;
            break;
        }
    }
}

void adminPanel() {
    clearScreen();
    cout<<"\n\t";
    cout << "***** Admin Panel *****" << endl;
    sleepTime(200);
    cout<< "\n\t\t1. Create" << endl;
    cout << "\t\t2. Read" << endl;
    cout << "\t\t3. Update" << endl;
    cout << "\t\t4. Delete" << endl;
    cout << "\t\t5. Back\n\n" << endl;

    int choice;
    do
    {
        coffeeList *ls = new coffeeList();
        readCoffeeList(ls);
        cout<<"\t\tEnter Choice (1 - 3):  ";
        cin >> choice;

        if(choice == 1) {
            displayCoffeeList(ls);
            createCoffee(ls);
            adminPanel();
        }
        else if(choice == 2) {
            clearScreen();
            displayCoffeeList(ls);
            waitForInput();
            adminPanel();
        }

    }   while(choice < 1 || choice > 5);

    sleepTime(200);
}