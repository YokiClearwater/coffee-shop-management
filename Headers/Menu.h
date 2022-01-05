#include <vector>

void mainMenu();
void buyCoffee(UserInfo *ul);
void adminPanel();
void bestBuy();
void bestItem();
void removeAllCoffeeItem();

void mainMenu(UserInfo *ul) {
    int choice;
    
    do {
        clearScreen();
        cout<<"\n\t";
        cout << "***** Main Menu *****" << endl;
        sleepTime(200);
        cout<<"\n\t\t1. Ordering Coffee\n\t\t2. Admin Panel\n\t\t3. Back\n\n";
        sleepTime(200);
        cout<<"\t\tEnter Choice:  ";
        // cin >> choice;
        errorInputHandling(&choice);


        if(choice == 1) {
            buyCoffee(ul);
            sleepTime(1000);
            clearScreen();
        }
        else if(choice == 2) {
            if(verifyAdmin(ul->userName)) {
                adminPanel();
            }
            else {
                cout << "You're not logging in with an administrator account." << endl;
                waitForInput();
            }
            clearScreen();
        }
        else if(choice == 3) {
            break;
        }
        else {
            cout << "\t\tWrong Input!!" << endl;
        }
    }   while(true);
    
}

void buyCoffee(UserInfo *ul) {
    coffeeList *menu = createCoffeeList();
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

        cout<<"\t\t\t\tQuantity: "; errorInputHandling(&quantity);

        while(quantity <= 0)
        {
            cout<<"\n\t\t\tQuantity must be greater than zero. You can cancel order after input the quantity.\n";
            cout<<"\t\t\t\tQuantity: "; 
            errorInputHandling(&quantity);
        }

        cout<<"\t\t\t\tPrice to pay: "<< (item->price)*quantity <<" $\n";
        cout<<"\tPress 1 to confirm or press 2 to cancel order: "; errorInputHandling(&ff);
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
        errorInputHandling(&anotherdrink);

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
            int cc; cout <<"\t\t\tPress any number to go back to main menu: ";
            errorInputHandling(&cc);
            break;
        }
    }
}

void adminPanel() {  
    int choice;
    string itemID;
    do {
        clearScreen();
        cout<<"\n\t";
        cout << "***** Admin Panel *****" << endl;
        sleepTime(200);
        cout<< "\n\t\t1. Create " << endl;
        cout << "\t\t2. Read" << endl;
        cout << "\t\t3. Update" << endl;
        cout << "\t\t4. Delete" << endl;
        cout << "\t\t5. Total Earning" << endl;
        cout << "\t\t6. View Sales History" << endl;
        cout << "\t\t7. Best Customer" << endl;
        cout << "\t\t8. Most Sale Items" << endl;
        cout << "\t\t9. View Registered User" << endl;
        cout << "\t\t10. Add another administrator" << endl;
        cout << "\t\t11. Delete All Coffee Item" << endl;
        cout << "\t\t12. Back\n\n" << endl;

        coffeeList *ls = createCoffeeList();
        readCoffeeList(ls);
        cout<<"\t\tEnter Choice:  ";
        errorInputHandling(&choice);

        if(choice) {
            clearScreen();
        }

        if(choice == 1) {
            // clearScreen();
            displayCoffeeList(ls);
            createCoffee(ls);
            // adminPanel();
        }
        else if(choice == 2) {
            // clearScreen();
            displayCoffeeList(ls);
            waitForInput();
            // adminPanel();
        }
        else if(choice == 3) {
            // clearScreen();
            displayCoffeeList(ls);
            updateCoffee(ls, itemID);
            // adminPanel();
        }
        else if(choice == 4) {
            // clearScreen();
            displayCoffeeList(ls);
            deleteCoffee(ls, itemID);
            clearScreen();
            cout << "\t\tAfter Deletion" << endl;
            displayCoffeeList(ls);
            writeCoffeeList(ls);
            waitForInput();
        }
        else if(choice == 5) {
            // clearScreen();
            saleList *sl = readSaleHistory();
            saleWriteTotalCash(sl);
            waitForInput();
        }
        else if(choice == 6) {
            // clearScreen();
            viewUserSaleHistory();
            waitForInput();
        }
        else if(choice == 7) {
            // clearScreen();
            bestBuy();
            waitForInput();
        }
        else if(choice == 8) {
            // clearScreen();
            bestItem();
            waitForInput();
        }
        else if(choice == 9) {
            // clearScreen();
            displayRegisteredUser();
            waitForInput();
        }
        else if(choice == 10) {
            addAdmin();
        }
        else if(choice == 11) {
            removeAllCoffeeItem();
            waitForInput();
        }
        else if(choice == 12) {
            break;
        }
        else {
            clearScreen();
            cout << "\t\tWrong Input!!" << endl;
        }

    }   while(true);

    sleepTime(200);
}

void bestBuy() {
    saleList *ul = readSaleHistory();
    saleList *U2 = sumSaleList(ul); 

    saleElement *bestUser = bestCustomer(U2);

    cout << "\nOur Best Customer is " << bestUser->userId << " spending $ " << bestUser->coffeePrice << endl;
}

void bestItem() {
    saleList *ul = readSaleHistory();
    saleList *U2 = sortCoffeeReceipt(ul); 
    saleElement *bestCoffee = bestSale(U2);

    coffeeList *ls = createCoffeeList();
    readCoffeeList(ls);
    coffeeElement *item = searchItem(ls, bestCoffee->coffeeId);

    cout << "\nBest Item: " << bestCoffee->coffeeId << "." << item->name <<  ", Quantity: " << bestCoffee->qty << endl;
}

void removeAllCoffeeItem() {
    string str;
    cout << "\t\tAre you sure you want to delete all item? (Y/N): " << endl;
    cin >> str;
    if(str == "Y" || str == "y" || str == "yes" || str == "YES") {
        coffeeList *ls = createCoffeeList();
        readCoffeeList(ls);
        deleteAllCoffees(ls);
        writeCoffeeList(ls);
        cout << "All coffee items in the menu are deleted!!" << endl;
    }
    else if(str == "N" || str == "n" || str == "no" || str == "NO") {
        cout << "Any item wasn't deleted." << endl;
    }
    else {
        cout << "\t\tDelete Failed!!!" << endl;
    }
}