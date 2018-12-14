#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element{
    int key;
    Element *next, *prev;
};

struct List2W{
    Element *head;
};

void init(List2W& l){ //+
    l.head = NULL;
}

void insertHead(List2W& l, int x){ //++
    Element *newEl = new Element;
    newEl->key = x;
    Element *p = l.head;

    if(p == NULL){  //if there's no head
        newEl->prev = newEl;
        newEl->next = newEl;
        l.head = newEl;
    }
    else{
        newEl->next = p;
        newEl->prev = p->prev;
        p->prev = newEl;
        if(newEl->prev != NULL)
            newEl->prev->next = newEl;//make it circularly
        l.head = newEl;
    }
}

bool deleteHead(List2W& l, int &value){ //++
    if (l.head != NULL)
    {
        Element *p = l.head;
        value = p->key;
        if(p->next != p && p->next != NULL) {
            p->next->prev = l.head->prev;
            p->prev->next = l.head->next;
            l.head = p->next;
        }
        else if(p->next == l.head || p->next == NULL || p->prev == NULL || l.head == NULL){  //if there's only one element(one head)
            l.head = NULL;
            p->next = NULL;
            p->prev = NULL;
            delete p;
            return true;
        }
        delete p;
        return true;
    }
    return false;
}

void insertTail(List2W& l, int x){  //+
    Element *newEl = new Element;
    newEl->key = x;
    Element *p = l.head;

    if(p != NULL){
        while(p->next != l.head && p->next != NULL)
            p = p->next;    //go to current tail
        newEl->next = l.head;
        p->next = newEl;
        newEl->prev = p;
        l.head->prev = newEl;
    }
    else{
        newEl->next = newEl;
        newEl->prev = newEl;
        l.head = newEl;
    }
}

void clearList(List2W& l){ //++
    int tmp; //temporary variable
    while (deleteHead(l, tmp));
}

bool deleteTail(List2W& l, int &value){
    if(l.head != NULL){
        Element *p = l.head->prev;  //tail
        if(l.head->prev == l.head){
            value = l.head->key;
            l.head = NULL;
            return true;
        }
        value = p->key;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        return true;
    }
    return false;
}

int findValue(List2W& l, int value){ //++
    int index = 0;
    Element *p = l.head;

    if(p != NULL) {
        if (p->key == value)
            return index;

        index++;
        p = p->next;

        while (p->key != value && p != l.head)  //p != l.head to exit an infinite loop(no such value was found)
        {
            p = p->next;
            index++;
        }
        if (p == l.head)
            return -1;
        return index;
    }
    return -1;
}

void removeAllValue(List2W& l, int value) { //+
    while (l.head != NULL && l.head->key == value) {
        int tmp;    //tmp variable for deleteHead function
        deleteHead(l, tmp);
    }

    if(l.head != NULL) {
        Element *p = l.head->next;
        if (p != NULL) {
            while (p != l.head) {
                if (p->key == value) {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                }
                p = p->next;
            }
        }
    }
}

void showListFromHead(List2W& l){ //++
    if (l.head != NULL)
    {
        Element *p = l.head;
        cout << p->key << ",";
        while (p->next != l.head)
        {
            cout << p->next->key << ",";
            p = p->next;
        }
    }
    cout << endl;
}

void showListFromTail(List2W& l){ //+
    if (l.head != NULL)
    {
        Element *p = l.head;

        while(p->next != l.head)
            p = p->next;    //go to current tail

        Element *pTail = p;

        cout << p->key << ",";
        while (p->prev != pTail)
        {
            cout << p->prev->key << ",";
            p = p->prev;
        }
    }
    cout << endl;
}

void addList(List2W& l1,List2W& l2){
    if(l1.head == l2.head || l2.head == 0)
        return;
    if(l1.head == 0){
        l1 = l2;
        init(l2);
        return;
    }

    Element *p = l1.head->prev;

    l1.head->prev->next = l2.head;
    l1.head->prev = l2.head->prev;
    l2.head->prev = p;
    l1.head->prev->next = l1.head;

    init(l2);
}

void deleteEvery(List2W& l){
    int index = 0;

    if(l.head != NULL) {
        Element *p = l.head;

        do{
            if(index % 2 == 0){
                p = p->next;
                index++;
                continue;
            }
            Element *ptr;
            ptr = p;

            if(p == l.head->prev){
                int tmp;
                deleteTail(l, tmp);
                break;
            }

            p->prev->next = p->next;
            p->next->prev = p->prev;
            index++;
            p = p->next;
            delete ptr;
        }while(p != l.head && l.head != NULL);
    }
}

void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    List2W *list;
    int currentL=0;
    int value;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }


        // zero-argument command
        if(isCommand(command,"DH")) //*
        {
            int retValue;
            bool retBool=deleteHead(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        if(isCommand(command,"DT")) //*
        {
            int retValue;
            bool retBool=deleteTail(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }

        if(isCommand(command,"SH")) //*
        {
            showListFromHead(list[currentL]);
            continue;
        }

        if(isCommand(command,"ST")) //*
        {
            showListFromTail(list[currentL]);
            continue;
        }

        if(isCommand(command,"CL")) //*
        {
            clearList(list[currentL]);
            continue;
        }

        if(isCommand(command,"IN")) //*
        {
            init(list[currentL]);
            continue;
        }
        if(isCommand(command,"DE")) //*
        {
            deleteEvery(list[currentL]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"FV")) //*
        {
            int ret;
            ret=findValue(list[currentL],value);
            cout << ret << endl;
            continue;
        }

        if(isCommand(command,"RV")) //*
        {
            removeAllValue(list[currentL],value);
            continue;
        }


        if(isCommand(command,"AD")) //*
        {
            addList(list[currentL],list[value]);
            continue;
        }

        if(isCommand(command,"CH")) //*
        {
            currentL=value;
            continue;
        }

        if(isCommand(command,"IH")) //*
        {
            insertHead(list[currentL],value);
            continue;
        }

        if(isCommand(command,"IT")) //*
        {
            insertTail(list[currentL],value);
            continue;
        }

        if(isCommand(command,"GO")) //*
        {
            list=new List2W[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
}
