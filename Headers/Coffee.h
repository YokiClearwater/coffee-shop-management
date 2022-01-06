#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct coffeeElement
{
    string name, id;
    float price;
    coffeeElement *next;
    coffeeElement *prev;
};

struct coffeeList
{
    int n;
    coffeeElement *head;
    coffeeElement *tail;
};

coffeeList *createCoffeeList()
{
    coffeeList *ls = new coffeeList();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}

void insertCoffeeBegin(coffeeList *ls, string id, string name, float price)
{
    coffeeElement *node = new coffeeElement();
    node->id = id;
    node->name = name;
    node->price = price;

    node->next = ls->head;
    node->prev = NULL;
    if (ls->n == 0)
    {
        ls->tail = node;
    }
    if (ls->n != 0)
        ls->head->prev = node;
    ls->head = node;
    ls->n = ls->n + 1;
}

void insertCoffeeEnd(coffeeList *ls, string id, string name, float price)
{
    coffeeElement *node = new coffeeElement();
    if (ls->n == 0)
        insertCoffeeBegin(ls, id, name, price);
    else
    {
        node->id = id;
        node->name = name;
        node->price = price;

        node->next = NULL;
        node->prev = ls->tail;
        ls->tail->next = node;
        ls->tail = node;
        ls->n = ls->n + 1;
    }
}

void readCoffeeList(coffeeList *ls) {
    string id, name;
    float price;
    fstream file;
    coffeeElement *node = new coffeeElement();
    file.open("Data/CoffeeList.txt");
    while (file >> id >> name >> price)
    {
        insertCoffeeEnd(ls, id, name, price);
    }
    file.close();
}

void writeCoffeeList(coffeeList *ls) {
    ofstream file;
    file.open("Data/CoffeeList.txt");

    coffeeElement *temp = new coffeeElement();
    temp = ls->head;
    while(temp != NULL) {
        file << temp->id << "\t" << temp->name << "\t" << temp->price << endl;
        temp = temp->next;
    }

    file.close();
}

coffeeElement *searchItem(coffeeList *ls, string itemID) {
    coffeeElement *temp = ls->head;
    int count = 0;

    while(temp != NULL) {
        count++;
        if(temp->id == itemID) {
            break;
        }
        temp = temp->next;
    }  
    return temp;
}

void displayCoffeeList(coffeeList *ls) {
    coffeeElement *t;
    t = ls->head;

    cout << "\t\t---------------------------------------------\n";
    sleepTime(100);
    cout << "\t\t "
         << "ID" << setw(21) << "Drinks(Iced)" << setw(18) << "Price($)\n";
    sleepTime(100);
    cout << "\t\t---------------------------------------------\n";
    sleepTime(100);
    while (t != NULL)
    {
        cout << "\t\t " << t->id<< "." << setw(21) << t->name << setw(16) << t->price << "\n";
        t = t->next;
        sleepTime(100);
    }
    cout << "\t\t---------------------------------------------\n";
    sleepTime(100);
}

void createCoffee(coffeeList *ls) {
    string id, coffeename;
    float price;
    cout << "\t\tEnter ID: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    id = stringInput();

    while(!digitCheck(id)) {
        cout << "\t\tID must be digit." << endl;
        cout << "\t\tEnter ID: ";
        id = stringInput();
    }
    if(id.size() == 0) {return;}

    coffeeElement *item = searchItem(ls, id);

    while(item != NULL) {
        cout << "\t\tID exists!\n\t\tPlease enter the new ID!\n";
        cout << "\t\tEnter ID: ";
        id = stringInput();
        item = searchItem(ls, id);
    }

    cout << "\t\tEnter Coffee's Name: ";
    coffeename = stringInput();
    if(coffeename.size() == 0) {return;}
    cout << "\t\tEnter Coffee's Price: ";
    cin >> price;

    if(price == 0) {
        return;
    }

    insertCoffeeEnd(ls, id, coffeename, price);
    writeCoffeeList(ls);
}

void updateCoffee(coffeeList *ls, string itemID) {
    cout << "\t\tEnter ID to Search: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    itemID = stringInput();

    coffeeElement *temp = searchItem(ls, itemID);
    while(temp == NULL) {
        cout << "\t\tItem Not Found!! Enter ID Again: ";
        itemID = stringInput();
        temp = searchItem(ls, itemID);
    }

    string newName;
    float newPrice;
    int choice;

    do {
        cout << "\n\t\t1. Update Name Only" << endl;
        cout << "\t\t2. Update Price Only" << endl;
        cout << "\t\t3. Both" << endl;
        cout << "\t\t4. Back" << endl;
        cout << "\t\tEnter Choice: ";

        cin >> choice;
        if(choice == 1) {
            cout << "\t\tEnter Item Name: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newName = stringInput();
            temp->name = newName;
        }
        else if(choice == 2) {
            cout << "\t\tEnter Item Price: ";
            errorInputHandling(&newPrice);
            temp->price = newPrice;
        }
        else if(choice == 3) {
            cout << "\t\tEnter Item Name: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newName = stringInput();
            temp->name = newName;
            cout << "\t\tEnter Item Price: ";
            errorInputHandling(&newPrice);
            temp->price = newPrice;
        }
        else {
            cout << "\t\tWrong Input" << endl;
        }

    } while(choice != 4);

    if(newPrice == 0) {
        cout << "\t\tPrice can't be zero." << endl;
        return;
    }

    if(newName.size() == 0) {
        return;
    }

    writeCoffeeList(ls);
}

void deleteCoffee(coffeeList *ls, string itemID) {
    cout << "\t\tEnter ID to Delete: ";
    cin >> itemID;

    coffeeElement *del = searchItem(ls, itemID);

    while(del == NULL) {
        cout << "\t\tNot Found!! Enter ID Again: ";
        cin >> itemID;
        del = searchItem(ls, itemID);
    }

    if (ls->head == NULL || del == NULL)
        return;
 
    if (ls->head == del)
        ls->head = del->next;
    
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    if (del->prev != NULL) {
        del->prev->next = del->next;
        if(del->next == NULL) {
            ls->tail = del->prev;
        }
    }

    delete del;
    ls->n = ls->n - 1;
}

void deleteAllCoffees(coffeeList *ls) {
    coffeeElement *temp = new coffeeElement();
    while(ls->head != NULL) {
        temp = ls->head;
        ls->head = ls->head->next;
        delete temp;
    }

    ls->tail = NULL;
    ls->n = 0;
}