using namespace std;
struct element{
    string ID;
    string pword;
    element *next;
};

struct List{
    int n;
    element *head;
    element *tail;

};
List* makeEmptyList(){
    List *ls;
    ls = new List;

    ls -> n=0;
    ls -> head=NULL;
    ls -> tail=NULL;

    return ls;
}
void addBegin(List *ls, string newID, string newpword){
    element *e;
    e = new element;
    e->ID = newID;
    e->pword = newpword;

    e->next = ls->head;
    ls->head = e;

    if(ls->n==0){
        ls->tail =e;
    }
    ls->n = ls->n +1;
}
//for display our list
void displayList(List *ls){
    element *t;
    t= ls->head;

    while(t!=NULL){
        cout<<t->ID<<" "<<t->pword<<"\n";
        t= t->next;
    }
}
// for adding from the end
void addEnd(List *ls, string newID, string newpword){
    if(ls->n==0)
    {
        addBegin(ls, newID, newpword);
    }
    else
    {
        element *e;
        e= new element();
        e->ID = newID;
        e->pword = newpword;
        e->next=NULL;
        //update tail pointer
        ls->tail->next=e;
        ls->tail=e;
        ls->n=ls->n+1;
    }
}
void readToList(List *user){
    string ID, passw;

    fstream file;
    file.open("User Identity .txt", ios::in);
    while(!file.eof())
    {
        file>>ID>>passw;
        addEnd(user, ID, passw);
    }
    file.close();
}



struct coffee{
    string CoID, name;
    float price;
    coffee *next;
};

struct coffee_list{
    int n;
    coffee *head;
    coffee *tail;

};
coffee_list* makeCoffeeList(){
    coffee_list *ls;
    ls = new coffee_list;

    ls -> n=0;
    ls -> head=NULL;
    ls -> tail=NULL;

    return ls;
}
void addToBegin(coffee_list *ls, string newID, string newName, int newPrice){
    coffee *e;
    e = new coffee;
    e->CoID = newID;
    e->price = newPrice;
    e->name= newName;

    e->next = ls->head;
    ls->head = e;

    if(ls->n==0){
        ls->tail =e;
    }
    ls->n = ls->n +1;
}
void display(coffee_list *ls){
    coffee *t;
    t= ls->head;
    cout<<"\t\t---------------------------------------------\n";
    Sleep(100);
    cout<<"\t\t "<<"ID"<<setw(21)<<"Drinks(Iced)"<<setw(18)<<"Price($)\n";
    Sleep(100);
    cout<<"\t\t---------------------------------------------\n";
    Sleep(100);
    while(t!=NULL){
        cout<<"\t\t "<<t->CoID<<"."<<setw(21)<<t->name<<setw(16)<<t->price<<"\n";
        t= t->next;
        Sleep(100);
    }
    cout<<"\t\t---------------------------------------------\n";
    Sleep(100);
}
// for adding from the end
void addToEnd(coffee_list *ls, string newID, string newname, int newprice){
    if(ls->n==0)
    {
        addToBegin(ls, newID, newname, newprice);
    }
    else
    {
        coffee *e;
        e= new coffee();
        e->CoID = newID;
        e->name = newname;
        e->price = newprice;
        e->next=NULL;
        //update tail pointer
        ls->tail->next=e;
        ls->tail=e;
        ls->n=ls->n+1;
    }
}
void get_coffee_menu(coffee_list *menu){
    fstream ff;
    string CoID, CoName; int CoPrice;
    ff.open("Coffee_Data.txt", ios::in);
    while(!ff.eof())
    {
        ff>>CoID>>CoName>>CoPrice;
        addToEnd(menu, CoID, CoName, CoPrice);
    }
    ff.close();
}
void HideInput()
{
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}
void LogInUser(List *ls, coffee_list *menu){
    element *tmp;
    coffee *temMenu, *checkID;
    int counter=0, compare=0;
    int anotherdrink, kaev[10], tlai[10], invoice_price=0, count_tenh=0;
    string name_lbos[10];
    string d;
    string password;
    tmp= ls->head;
    temMenu= menu->head;
    checkID= menu->head;
        cout<<"\tEnter your user name: ";
        cin>>d;
        HideInput();
        cout<<"\tEnter your password: ";
        cin>>password;

    while(tmp!=NULL)
    {
        if(tmp->ID==d)
        {
            //counter=1;
            if(tmp->pword==password)
            {
                compare=1;
            }
        }
    tmp=tmp->next;
    }
    if( compare==1)
        {
            system("CLS");
            cout<<"\n\t\t## Login successful!\n";
            Sleep(700);
            string user_id, coffee_id;
            int qunt, ff;
            float price;

            while(true){

            display(menu);
            cout<<"\t\t\t\tEnter drink ID to order: "; cin>>coffee_id;
            while(coffee_id!=checkID->CoID)
            {
                if(checkID->next==NULL)
                {
                    cout<<"\n\t\t\t\tAttention, Invalid coffeeID! Please enter coffee ID again to order: "; cin>>coffee_id;
                    checkID= menu->head;
                    continue;
                }
                checkID=checkID->next;
            }
            checkID= menu->head;
            cout<<"\t\t\t\tQuantity: "; cin>>qunt;
            while(qunt<=0)
            {
                cout<<"\n\t\t\tQuantity must be greater than zero. You can cancel order after input the quantity.\n";
                cout<<"\t\t\t\tQuantity: "; cin>>qunt;
            }
            while(temMenu->CoID!=coffee_id)
            {
                temMenu=temMenu->next;
            }

            cout<<"\t\t\t\tPrice to pay: "<<temMenu->price*qunt<<" $\n";
            cout<<"\tPress 1 to confirm or press 2 to cancel order: "; cin>>ff;
            Sleep(500);
            system("CLS");
            if(ff==1)
            {
                name_lbos[count_tenh]=temMenu->name;
                tlai[count_tenh]=temMenu->price*qunt;
                kaev[count_tenh]=qunt;
                //cout<<"\n\t\t#### Thank you for ordering our drinks ####\n";
                fstream f3;
                f3.open("Sale history.txt", ios::app);

                f3<<d<<" "<<coffee_id<<" "<<qunt<<" "<<qunt*temMenu->price<<"\n";

                f3.close();
                count_tenh++;
            }

            temMenu= menu->head;
            cout<<"\n\tType 1 to make another order or other number to finish order: ";
            cin>>anotherdrink;

            if(anotherdrink==1)
            {
                continue;
            }
            else
            {
                    Sleep(500);
                    system("CLS");
                    if(count_tenh==0){break;}
                    cout<<"\n\t\tWe are printing our invoice";
                    for(int ii=1; ii<=10; ii++)
                    {
                        cout<<". ";
                        Sleep(300);
                    }
                    cout<<"\n\n\t\t  "<<"Drink(s)"<<setw(19)<<"Quantity"<<setw(19)<<"Price($)\n";
                    cout<<"\t\t----------------------------------------------\n";
                    for(int kkk=0; kkk<count_tenh; kkk++)
                    {
                        invoice_price=invoice_price+tlai[kkk];
                        cout<<"\t\t "<<setw(10)<<name_lbos[kkk]<<setw(15)<<kaev[kkk]<<setw(16)<<tlai[kkk]<<"\n";
                    }
                    cout<<"\t\t----------------------------------------------\n";
                    cout<<"\t\t\tOverall price to pay is $"<<invoice_price<<"\n";
                    cout<<"\n\t\t#### Thank you for ordering our drinks ####\n";
                    int sus; cout<<"\t\t\tPress any number to go back to costumer panel: "; cin>>sus;
                    break;
            }




            }
        }
        else
        {
            cout<<"\n\t\tInvalid user ID or password. If you are a new user please sign up\n";
            int sus; cout<<"\t\tPress any number to continue: "; cin>>sus;
            counter=0; compare=0;
        }

}
int loginOrSignup(){
    int cc, n;
    char Wcome[50]="***** WELCOME TO COSTUMER PANEL *****";
    system("CLS");
    cout<<"\n\t";
    n=strlen(Wcome);
    Sleep(500);
    for(int ii=0; ii<n; ii++)
    {
        cout<<Wcome[ii];
        Sleep(70);
    }
    Sleep(200);
    cout<<"\n\t\t1. Login\n\t\t2. Sign up\n\t\t3. Exit\n\n";
    Sleep(200);
    do
    {
        cout<<"\t\tEnter option 1-3:  ";
        cin>>cc;
    }while(cc<1 || cc>3);
    return cc;

}
void signUp(List *ls, coffee_list *menu){
    int anotherdrink, kaev[10], tlai[10], invoice_price=0, count_tenh=0;
    string name_lbos[10];
    string password, password2;
    string ii;
    element *checkUsername;
    coffee *checkID;
    int good=0;
    checkUsername=ls->head;
    checkID= menu->head;
    while(true)
    {
        cout<<"\t\tEnter a user name: ";
        cin>>ii;
        do
        {
            HideInput();
            cout<<"\t\tCreate your own password: ";
            cin>>password;
            HideInput();
            cout<<"\n\t\tRetype to verify password: ";
            cin>>password2;
            if(password!=password2)
            {
                cout<<"\n\tPassword no match! Try again.\n";
            }

        }while(password!=password2);
        while(checkUsername!=NULL)
        {
            if(ii==checkUsername->ID)
            {
                good=1; break;
            }
            checkUsername=checkUsername->next;
        }
        if(good==1)
        {
            cout<<"\n\t\tThis user name was taken, try putting any number behind your name.\n\n";
            good=0;
            continue;
        }
        else if(good==0)
        {
            break;
        }
    }
    system("CLS");
    cout<<"\t\tSign up successful!\n";
    Sleep(700);
    fstream file;
    file.open("User Identity .txt", ios::app);

    file<<ii<<" "<<password<<"\n";

    file.close();

    coffee *temMenu;
    temMenu= menu->head;
    string user_id, coffee_id;
    int qunt, ff;
    float price;

    while(true){

    display(menu);
    cout<<"\t\t\t\tEnter drinks ID to order: "; cin>>coffee_id;
    while(coffee_id!=checkID->CoID)
        {
            if(checkID->next==NULL)
            {
                cout<<"\n\t\t\t\tAttention, Invalid coffeeID! Please enter coffee ID again to order: "; cin>>coffee_id;
                checkID= menu->head;
                continue;
            }
            checkID=checkID->next;
        }
        checkID= menu->head;
        cout<<"\t\t\t\tQuantity: "; cin>>qunt;
        while(qunt<=0)
            {
                cout<<"\n\t\t\tQuantity must be greater than zero. You can cancel order after input the quantity.\n";
                cout<<"\t\t\t\tQuantity: "; cin>>qunt;
            }
        while(temMenu->CoID!=coffee_id)
        {
            temMenu=temMenu->next;
        }
        cout<<"\t\t\t\t## Price to pay: "<<temMenu->price*qunt<<" $\n";
        cout<<"\tPress 1 to confirm or press 2 to cancel order: "; cin>>ff;
        Sleep(500);
        system("CLS");
        if(ff==1)
        {
            name_lbos[count_tenh]=temMenu->name;
            tlai[count_tenh]=temMenu->price*qunt;
            kaev[count_tenh]=qunt;

            fstream file;
            file.open("Sale history.txt", ios::app);

            file<<ii<<" "<<coffee_id<<" "<<qunt<<" "<<qunt*temMenu->price<<"\n";

            file.close();
            count_tenh++;
        }
        temMenu= menu->head;

        cout<<"\n\tType 1 to make another order or other number to finish order: ";
        cin>>anotherdrink;
        if(anotherdrink==1)
        {
            continue;
        }
        else
        {
                Sleep(500);
                system("CLS");
                if(count_tenh==0){break;}
                cout<<"\n\t\tWe are printing our invoice";
                for(int ii=1; ii<=10; ii++)
                {
                    cout<<". ";
                    Sleep(300);
                }
                cout<<"\n\n\t\t  "<<"Drink(s)"<<setw(19)<<"Quantity"<<setw(19)<<"Price($)\n";
                cout<<"\t\t----------------------------------------------\n";
                for(int kkk=0; kkk<count_tenh; kkk++)
                {
                    invoice_price=invoice_price+tlai[kkk];
                    cout<<"\t\t "<<setw(10)<<name_lbos[kkk]<<setw(15)<<kaev[kkk]<<setw(16)<<tlai[kkk]<<"\n";
                }
                cout<<"\t\t----------------------------------------------\n";
                cout<<"\t\t\tOverall price to pay is $"<<invoice_price<<"\n";
                cout<<"\n\t\t#### Thank you for ordering our drinks ####\n";
                int sus; cout<<"\t\t\tPress any number to go back to costumer panel: "; cin>>sus;
                break;
        }


    }
}

