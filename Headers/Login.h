#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct UserInfo{
    string userName;
    string pword;
    UserInfo *next;
    UserInfo *prev;
};

struct UserList {
    int n;
    UserInfo *head;
    UserInfo *tail;
};

UserList* makeEmptyList(){
    UserList *ls;
    ls = new UserList;

    ls -> n=0;
    ls -> head = NULL;
    ls -> tail = NULL;

    return ls;
}
void addBegin(UserList *ls, string newName, string newpword){
    UserInfo *user;
    user = new UserInfo;
    user->userName = newName;
    user->pword = newpword;
    user->prev = NULL;
    user->next = ls->head;

    if(ls->n==0){
        ls->tail = user;
    }

    if(ls->n != 0) {
        ls->head->prev = user;
    }

    ls->head = user;
    ls->n = ls->n +1;
}
//for display our list
void displayList(UserList *ls){
    UserInfo *t;
    t= ls->head;

    while(t!=NULL){
        cout << t->userName << " " << t->pword<<"\n";
        t= t->next;
    }
}

// for adding from the end
void addEnd(UserList *ls, string newName, string newpword){
    if(ls->n==0)
    {
        addBegin(ls, newName, newpword);
    }
    else
    {
        UserInfo *user;
        user = new UserInfo();
        user->userName = newName;
        user->pword = newpword;
        user->next = NULL;
        user->prev = ls->tail;
        //update tail pointer
        ls->tail->next = user;
        ls->tail = user;
        ls->n=ls->n+1;
    }
}

UserList *readUserInfo(){
    string userName, password;

    fstream file;
    file.open("Data/UserInfo.txt");

    UserList *user = makeEmptyList();

    while(file >> userName >>password)
    {
        addBegin(user, userName, password);
    }
    
    file.close();

    return user;
}

void writeUserInfo(UserList *ls) {
    ofstream file;
    file.open("Data/UserInfo.txt");

    UserInfo *temp = new UserInfo();
    temp = ls->head;
    while(temp != NULL) {
        file << temp->userName << "\t" << temp->pword << endl;
        temp = temp->next;
    }

    file.close();
}

UserInfo *searchUserInfo(UserList *ls, string name) {
    UserInfo *temp = ls->head;
    int count = 0;

    while(temp != NULL) {
        count++;
        if(temp->userName == name) {
            break;
        }
        temp = temp->next;
    }  
    return temp;
}

int loginOrSignup(){
    int cc;
    string welcome = "***** WELCOME TO COSTUMER PANEL *****";
    clearScreen();
    cout<<"\n\t";
    
    cout << welcome << endl;
    
    sleepTime(200);
    cout<<"\n\t\t1. Login\n\t\t2. Sign up\n\t\t3. Exit\n\n";
    sleepTime(200);
    do
    {
        cout<<"\t\tEnter option 1-3:  ";
        cin >> cc;

    }   while(cc<1 || cc>3);

    return cc;
}

void signUp(UserList *ls) {
    string username, password, confirmPass;
    
        cout << "Enter Username: ";
        cin >> username;
        UserInfo *checkUsername = searchUserInfo(ls, username);

        while(checkUsername != NULL) {
            cout<<"This user name is already taken." << endl;
            cout << "\t\tEnter another username: ";
            cin >> username;
            checkUsername = searchUserInfo(ls, username);
        }


        do {
            cout << "\t\tCreate your own password: ";
            cin >> password;
            cout << "\t\tConfirm password: ";
            cin >> confirmPass;
            if (password != confirmPass) {
                cout << "\t\tPassword Doesn't Match!! Try Again!!" << endl;
            }
        }   while(password != confirmPass);

    addEnd(ls, username, password);
    writeUserInfo(ls);
}

UserInfo *logIn() {
    UserList *LL = readUserInfo();
    string userName, password;

    cout << "\t\tEnter Username: ";
    cin >> userName;
    cout << "\t\tEnter Password: ";
    cin >> password;

    UserInfo *U1 = searchUserInfo(LL, userName);
    while(true) {
        if(U1 != NULL && password == U1->pword) {
            break;
        }
        else {
            cout << "\t\tIncorrect Username or Password!! Enter Again!!" << endl;
            cout << "\t\tEnter Username: ";
            cin >> userName;
            cout << "\t\tEnter Password: ";
            cin >> password;
            U1 = searchUserInfo(LL, userName);
        }
    }

    return U1;
}