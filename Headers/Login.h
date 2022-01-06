#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string salt = "cafe$";

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

UserList* createUserList(){
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

UserList *readUserInfo(string filename){
    string userName, password;

    fstream file;
    file.open(filename);

    UserList *user = createUserList();

    while(file >> userName >>password)
    {
        addBegin(user, userName, password);
    }
    
    file.close();

    return user;
}

void writeUserInfo(UserList *ls, string filename) {
    ofstream file;
    file.open(filename);

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
    cout<<"\n\t\t1. Login\n\t\t2. Sign up\n\t\t3. ReadMe/Help\n\t\t4. Exit\n\n";
    sleepTime(200);
    do
    {
        cout<<"\t\tEnter Option: ";
        cin >> cc;
        if(cin.fail()) {
            errorInputHandling(&cc);
        }

    }   while(cc < 1 || cc > 4);

    return cc;
}

void signUp(UserList *ls) {
    string username, password, confirmPass;
    bool flag = true;
    delayPrint("Sign Up A New Account: ");
    
        cout << "\t\tEnter Username: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        username = stringInput();
        
        UserInfo *checkUsername = searchUserInfo(ls, username);

        while(checkUsername != NULL) {
            cout<<"\t\tThis user name is already taken." << endl;
            cout << "\t\tEnter another username: ";
            username = stringInput();
            checkUsername = searchUserInfo(ls, username);
        }

        do {
            inputPass(&password, "\t\tCreate your own password: ");
            if(password.size() == 0) {
                flag = false;
            }
            password = SHA256::encrypt(password + salt);

            inputPass(&confirmPass, "\t\tConfirm password: ");
            confirmPass = SHA256::encrypt(confirmPass + salt);
            
            

            if (password != confirmPass) {
                cout << "\t\tPassword Doesn't Match!! Try Again!!" << endl;
            }
        }   while(password != confirmPass);

    // condition not to add empty username or password to files.
    if(flag == false  || username.size() == 0) {
        cout << "\n\t\tSigned Up Failed!!!" << endl;
        cout << "\n\t\tPress ENTER to continue....";
        cin.get();
        return;
    }
    else {
        addEnd(ls, username, password);
        writeUserInfo(ls, "Data/UserInfo.txt");
    }
}

UserInfo *logIn() {
    UserList *LL = readUserInfo("Data/UserInfo.txt");
    string userName, password;

    delayPrint("Logging In: ");


    cout << "\t\tEnter Username: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    userName = stringInput();

    inputPass(&password, "\t\tEnter Password: ");
    password = SHA256::encrypt(password + salt);

    UserInfo *U1 = searchUserInfo(LL, userName);
    int attempt = 0, flag = 5;
    while(true) {
        if(U1 != NULL && password == U1->pword) {
            break;
        }
        else {
            attempt++;
            if(attempt == flag) {
                return NULL;
            }
            cout << "\t\tIncorrect Username or Password!! Enter Again!!" << endl;
            cout << "\t\tYou have " << (flag - attempt) << " attempt left." << endl;

            cout << "\t\tEnter Username: ";
            userName = stringInput();
            inputPass(&password, "\t\tEnter Password: ");
            password = SHA256::encrypt(password + salt);
            U1 = searchUserInfo(LL, userName);
        }
    }
    return U1;
}

void displayRegisteredUser() {
    UserList *ul = readUserInfo("Data/UserInfo.txt");
    UserInfo *temp = ul->head;
    delayPrint("Registered Users: \n\t\t------------------------");
    while(temp != NULL) {
        cout << "\t\t" << temp->userName << endl;
        temp = temp->next;
    }
    cout << endl;
}

void addAdmin() {
    UserList *ul = readUserInfo("Data/UserInfo.txt");
    string name;
    delayPrint("Adding a new administrator");

    cout << "\t\tEnter Username: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    name = stringInput();

    if(name.size() == 0) {
        cout << "\t\tFailed!! Name Input was Empty!!";
        cin.get();
        return;
    }

    UserInfo *user = searchUserInfo(ul, name);
    while(user == NULL) {
        cout << "\t\tUser not found. Enter Again: ";
        name = stringInput();
        user = searchUserInfo(ul, name);
    }

    UserList *adminList = readUserInfo("Data/Admin.txt"); 
    UserInfo *admin = searchUserInfo(adminList, name);
    if(admin != NULL) {
        cout << "\t\tAdmin already existed." << endl;
        return;
    }
    else {
        addBegin(adminList, user->userName, user->pword);
        writeUserInfo(adminList, "Data/Admin.txt");
    }
}

bool verifyAdmin(string name) {
    UserList *ul = readUserInfo("Data/Admin.txt");

    UserInfo *user = searchUserInfo(ul, name);
    if(user != NULL) {
        return true;
    }
    return false;
}

int longestUserName() {
    UserList *ul = readUserInfo("Data/UserInfo.txt");
    UserInfo *temp, *max;
    temp = max = ul->head;

    while(temp != NULL) {
        if(temp->userName > max->userName) {
            max = temp;
        }
        temp = temp->next;
    }
    
    return max->userName.size();
}