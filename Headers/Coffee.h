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
    cout << "Enter ID: ";
    cin >> id;

    coffeeElement *item = searchItem(ls, id);

    while(item != NULL) {
        cout << "ID exists!\nPlease enter the new ID!\n";
        cout << "Enter ID: ";
        cin >> id;
        item = searchItem(ls, id);
    }

    cout << "Enter Coffee's Name: ";
    cin >> coffeename;
    cout << "Enter Coffee's Price: ";
    cin >> price;
    insertCoffeeEnd(ls, id, coffeename, price);
    writeCoffeeList(ls);
}