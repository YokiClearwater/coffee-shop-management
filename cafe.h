#include <iostream>
#include <fstream>
#include <iomanip>
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

bool fileExists(const string &name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
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
void readFromFile(coffeeList *ls)
{
    string id, name;
    float price;
    fstream file;
    coffeeElement *node = new coffeeElement();
    file.open("coffee_Data.txt", ios::in);
    while (!file.eof())
    {
        file >> id >> name >> price;
        insertCoffeeEnd(ls, id, name, price);
    }
    file.close();
}
void writeNewFile(coffeeList *ls)
{
    coffeeElement *node = new coffeeElement();
    node = ls->head;
    fstream file;

    file.open("Coffee_Data.txt", ios::out);
    while (node != NULL)
    {
        if (node->next != NULL)
        {
            file << node->id << " " << node->name << " " << node->price << "\n";
        }
        else
        {
            file << node->id << " " << node->name << " " << node->price;
        }
        node = node->next;
    }
    file.close();
}

void writeExistingFile(coffeeList *ls)
{
    coffeeElement *node = new coffeeElement();
    node = ls->head;
    fstream file;
    file.open("Coffee_Data.txt", ios::app);
    while (node != NULL)
    {
        file << "\n"
             << node->id << " " << node->name << " " << node->price;
        node = node->next;
    }
    file.close();
}
bool idExists(coffeeList *ls, string id)
{
    coffeeElement *node = new coffeeElement();
    node = ls->head;
    int flag = 0;
    while (node != NULL)
    {
        if (node->id == id)
        {
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 1)
        return true;
    else
        return false;
}

void findByID(coffeeList *ls, string id)
{
    coffeeElement *node = new coffeeElement();
    int flag = 0;
    node = ls->head;

    while (node != NULL)
    {
        if (node->id == id)
        {
            cout << "Coffee ID" << setw(20) << "Name" << setw(20) << "Price\n";
            cout << node->id << setw(25) << node->name << setw(25) << "$" << node->price << endl;
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 0)
    {
        cout << "ID not found!\n";
    }
}

void displayCoffee(coffeeList *ls)
{
    coffeeElement *node = new coffeeElement();
    node = ls->head;

    while (node != NULL)
    {
        cout << node->id << " " << node->name << " " << node->price << endl;
        node = node->next;
    }
}

void createCoffees(coffeeList *ls)
{
    string id, coffeename;
    float price;
    cout << "Enter ID ";
    cin >> id;
    if (idExists(ls, id))
    {
        do
        {
            cout << "ID exists!\nPlease enter the new ID!\n";
            cout << "Enter ID: ";
            cin >> id;
        } while (idExists(ls, id) == true);
    }
    cout << "Enter coffee name:";
    cin >> coffeename;
    cout << "Enter price";
    cin >> price;
    insertCoffeeBegin(ls, id, coffeename, price);
    writeNewFile(ls);
}

void editListByID(coffeeList *ls)
{
    coffeeElement *node = new coffeeElement();
    node = ls->head;
    int flag = 0;
    string id;
    cout << "Enter the ID to edit: ";
    cin >> id;
    while (node != NULL)
    {
        if (node->id == id)
        {
            cout << "Enter the new coffee name ";
            cin >> node->name;
            cout << "Enter the new coffee price ";
            cin >> node->price;
            flag = 1;
            break;
        }
        else
        {
            flag = 0;
        }
        node = node->next;
    }
    if (flag == 1)
    {
        cout << "Successfully updated the item with ID of " << id << endl;
    }
    else
    {
        cout << "ID not found!" << endl;
    }
}
void deleteCoffeeListByID(coffeeList *ls, string id)
{
    int flag = 0;
    coffeeElement *node = new coffeeElement();
    node = ls->head;
    while (node != NULL)
    {
        if (node->id == id)
        {
            if (node->next != NULL)
            {
                node->next->prev = node->prev;
            }
            if (node->prev != NULL)
            {
                node->prev->next = node->next;
            }
            delete node;
            flag = 1;
            break;
        }
        else
        {
            flag = 0;
        }
        node = node->next;
    }

    if (flag == 1)
    {
        cout << "Deleted the item with ID of " << id << endl;
    }
    else
    {
        cout << "ID not found!" << endl;
    }
}