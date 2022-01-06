#include <string>
#include <fstream>
#include <set>
#include <map>
using namespace std;

struct saleElement
{
    string userId, coffeeId;
    float coffeePrice;
    int qty;
    saleElement *next;
    saleElement *prev;
};

struct saleList
{
    int n;
    saleElement *head;
    saleElement *tail;
};

saleList *createSaleList()
{
    saleList *ls = new saleList();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}

void salesInsertBegin(saleList *ls, string userid, string coffeeid, int qty, float coffeePrice)
{
    saleElement *node = new saleElement();
    // node->saleId = saleId;
    node->userId = userid;
    node->coffeeId = coffeeid;
    node->coffeePrice = coffeePrice;
    node->qty = qty;
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

void salesInsertEnd(saleList *ls, string userid, string coffeeid, int qty, float coffeePrice)
{
    saleElement *node = new saleElement();
    if (ls->n == 0)
        salesInsertBegin(ls, userid, coffeeid, coffeePrice, qty);
    else
    {
        // node->saleId = saleId;
        node->userId = userid;
        node->coffeeId = coffeeid;
        node->coffeePrice = coffeePrice;
        node->qty = qty;
        node->next = NULL;
        node->prev = ls->tail;
        ls->tail->next = node;
        ls->tail = node;
        ls->n = ls->n + 1;
    }
}

saleList *readSaleHistory() {
    saleList *sl = createSaleList();

    ifstream file;
    file.open("Data/SaleHistory.txt");
    string userid, coffeeid;
    float coffeeprice;
    int qty;

    while (file >> userid >> coffeeid >> qty >> coffeeprice)
    {
        salesInsertBegin(sl, userid, coffeeid, qty, coffeeprice);
    }

    file.close();

    return sl;
}

void saleWriteTotalCash(saleList *ls) {
    saleElement *sale = ls->head;
    float totalCash = sale->coffeePrice;
    while (sale != NULL)
    {
        totalCash += sale->coffeePrice;
        sale = sale->next;
    }

    cout << "\n\n\t\tThe total sales in cash is: $" << totalCash << endl;
}

saleElement *bestCustomer(saleList *ul) {
    saleElement *max, *temp;
    temp = max = ul->head;

    while(temp != NULL) {
        if(temp->coffeePrice > max->coffeePrice) {
            max = temp;
        }
        temp = temp->next;
    }

    return max;
}

saleList *sumSaleList(saleList *ul) {
    saleList *U2 = createSaleList();
    saleElement *ptr = ul->head;
    set<string> str;

    while(ptr != NULL) {
        str.insert(ptr->userId);
        ptr = ptr->next;
    }

    set<string>::iterator it;

    
    for(it = str.begin(); it != str.end(); it++) {
        saleElement *temp;
        temp = ul->head;
        string coffeeID;
        int coffeeCount = 0;
        float price = 0;
        while(temp != NULL) {
            if(temp->userId == *it) {
                coffeeID = coffeeID + " " + temp->coffeeId ;
                coffeeCount += temp->qty;
                price += temp->coffeePrice;
            }
            temp = temp->next;
        }
        salesInsertEnd(U2, *it, coffeeID, coffeeCount, price);
    }

    return U2;
}

saleList *sortCoffeeReceipt(saleList *ul) {
    saleList *U2 = createSaleList();
    saleElement *ptr = ul->head;
    set<string> str;

    while(ptr != NULL) {
        str.insert(ptr->coffeeId);
        ptr = ptr->next;
    }

    set<string>::iterator it;

    
    for(it = str.begin(); it != str.end(); it++) {
        saleElement *temp;
        temp = ul->head;
        string userName = temp->userId;
        string coffeeID;
        int coffeeCount = 0;
        float price = 0;
        while(temp != NULL) {
            if(temp->coffeeId == *it) {
                coffeeCount += temp->qty;
                price += temp->coffeePrice;
            }
            temp = temp->next;
        }
        salesInsertBegin(U2, userName, *it, coffeeCount, price);
    }

    return U2;
}

saleElement *bestSale(saleList *ul) {
    saleElement *max, *temp;
    temp = max = ul->head;

    while(temp != NULL) {
        if(temp->qty > max->qty) {
            max = temp;
        }
        temp = temp->next;
    }

    return max;
}

struct UserHistory {
    string userId;
    map<string, pair<int, float>> history; // map(key, par<quantity, price>)
    UserHistory(): userId(string()){} //  Empty constructor
    UserHistory(string uuid) : userId(uuid){}
};

void add(UserHistory &userhistory, string cofId, int qty, float price){ // link the group of (coffee id, qty, price)->user id
    if(userhistory.history.find(cofId)==userhistory.history.end()){
        userhistory.history[cofId] = make_pair(qty,price);
    }
    else { 
        userhistory.history[cofId].first +=qty;
        userhistory.history[cofId].second +=price;
    }
}

void readSSV(ifstream &file, map<string, UserHistory> &user) {
    string uid, cid;
    int qty;
    float price;
    
    while(file >> uid >> cid >> qty >> price)
    {
        if(user.find(uid) == user.end()){
            user[uid] = UserHistory(uid);
            // cout << "UID: " << uid << endl;
        }
        add(user[uid], cid, qty, price);
    }
}

void viewUserSaleHistory() {
    map<string, UserHistory> users;
    ifstream saleHistory("Data/SaleHistory.txt");
    readSSV(saleHistory,users);

    coffeeList *ls = createCoffeeList();
    readCoffeeList(ls);
    
    int width = longestUserName() + 10;
    // cout << "\t\tName\t" << setw(13) << "Coffee ID" << setw(15)  << "Coffee Name" << setw(7); 
    // cout << "QTY" <<   setw(11) << "Price" << endl;
    cout << setw(width) << "Username" << setw(width) << "Coffee ID" << setw(20) << "Coffee Name";
    cout << setw(10) << "QTY" << setw(12) << "Price" << endl;

    string repeatUid;
    for(pair<const string,UserHistory> &tmpUser : users){ 
        coffeeElement *item = new coffeeElement();      
        for(pair<const string, pair<int, float>> &tmpItem: tmpUser.second.history){
            string coffeeID = tmpItem.first;
            width = longestUserName() + 10;
            if(repeatUid != tmpUser.first){
                cout<< "\n";
                cout << setw(width);
                cout << tmpUser.first;
            } else{
                cout << setw(width);
                cout << "\n";
                width = width*2;
            }
            item = searchItem(ls, coffeeID);

            cout << setw(width) << tmpItem.first<< setw(20) << item->name << setw(10) << tmpItem.second.first; 
            cout << setw(10) << tmpItem.second.second << " $ ";
            repeatUid = tmpUser.first;
        }
    }
    cout<<endl;
}

