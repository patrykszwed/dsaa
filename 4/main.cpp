#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element{
    int key;
    int value;
};

struct ElementLL{
    Element elem;
    ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
    ElementLL *sentinel;
};

void init(List2W& l){
    l.sentinel=new ElementLL();
    l.sentinel->next=l.sentinel;
    l.sentinel->prev=l.sentinel;
}

void insertElem(List2W & l, Element elem){
    ElementLL *newEl = new ElementLL;
    if(l.sentinel->next == l.sentinel) {    //the list is empty
        newEl->elem = elem;
        newEl->prev = l.sentinel;
        newEl->next = l.sentinel;
        l.sentinel->next = newEl;
        l.sentinel->prev = newEl;
    }
    else{
        newEl->elem = elem;
        ElementLL *p = l.sentinel->next;
        while(p->elem.key <= elem.key && p != l.sentinel){
            p = p->next;
        }
        if(p == l.sentinel){
            newEl->next = l.sentinel;
            newEl->prev = p->prev;
            p->prev->next = newEl;
            p->prev = newEl;
            return;
        }
        newEl->prev = p->prev;
        newEl->next = p;
        p->prev->next = newEl;
        p->prev = newEl;
    }
}

bool findKey(List2W & l,int key, Element &elem){
    if(l.sentinel->next != l.sentinel){
        ElementLL *p = l.sentinel->next;
        while(p->elem.key != key && p != l.sentinel)
            p = p->next;
        if(p == l.sentinel)
            return false;
        elem = p->elem;

        return true;
    }
    return false;
}

void removeAllKeys(List2W& l, int key){
    if(l.sentinel->next != l.sentinel){
        ElementLL *p = l.sentinel->next;

        while(p != l.sentinel){
            if(p->elem.key == key){
                ElementLL *ptr = p;

                p->prev->next = p->next;
                p->next->prev = p->prev;

                delete ptr;
            }

            p = p->next;
        }
    }
}

void showListFromHead(List2W& l){
    if (l.sentinel->next != l.sentinel)
    {
        ElementLL *p = l.sentinel->next;
        while (p != l.sentinel)
        {
            cout << p->elem.key << "(" << p->elem.value << ")" << ",";
            p = p->next;
        }
    }
    cout << endl;
}

void showListFromTail(List2W& l){
    if (l.sentinel->prev != l.sentinel)
    {
        ElementLL *p = l.sentinel->prev;
        while (p != l.sentinel)
        {
            cout << p->elem.key << "(" << p->elem.value << ")" << ",";
            p = p->prev;
        }
    }
    cout << endl;
}

void clearList(List2W &l) {
    ElementLL *p = l.sentinel->next;
    while(p != l.sentinel){
        ElementLL *ptr = p;

        p->prev->next = p->next;
        p->next->prev = p->prev;

        p = p->next;

        delete ptr;
    }
}

void addList(List2W& l1,List2W& l2) {
    if (l2.sentinel->next == l2.sentinel)
        return;
    if (l1.sentinel->next == l1.sentinel) {
        l1 = l2;
        clearList(l2);
        return;
    }

    ElementLL *p2 = l2.sentinel->next;
    ElementLL *p1 = l1.sentinel->next;

    while (p2 != l2.sentinel) {
        if(p1 == l1.sentinel){
            p1 = l1.sentinel->prev;
            while(p2 != l2.sentinel) {
                ElementLL *ptr = p2->next;
                p1->next->prev = p2;
                p2->next = p1->next;
                p1->next = p2;
                p2->prev = p1;

                p2 = ptr;
                p1 = p1->next;
            }
            return;
        }
        if (p2->elem.key < p1->elem.key) {
            ElementLL *ptr = p2->next;
            p1->prev->next = p2;
            p2->prev = p1->prev;
            p1->prev = p2;
            p2->next = p1;

            p2 = ptr;
            continue;
        } else if (p2->elem.key == p1->elem.key) {
            ElementLL *ptr = p2->next;
            p1->next->prev = p2;
            p2->next = p1->next;
            p1->next = p2;
            p2->prev = p1;

            p2 = ptr;
            continue;
        } else
            p1 = p1->next;
    }
}

void doubleEvery(List2W &l){
    if(l.sentinel->next != l.sentinel){
        ElementLL *p = l.sentinel->next;
        while(p != l.sentinel){
            ElementLL *ptr = new ElementLL;

            ptr->elem.key = p->elem.key;
            ptr->elem.value = p->elem.value;

            ptr->prev = p->prev;
            p->prev->next = ptr;
            p->prev = ptr;
            ptr->next = p;

            p = p->next;
        }
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

        // zero-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
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

        if(isCommand(command,"DS")) //*
        {
            doubleEvery(list[currentL]);
            continue;
        }

        if(isCommand(command,"IN")) //*
        {
            init(list[currentL]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(list[currentL], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        if(isCommand(command,"RK"))
        {
            removeAllKeys(list[currentL],value);
            continue;
        }

        if(isCommand(command,"CH"))
        {
            currentL=value;
            continue;
        }

        if(isCommand(command,"IE"))
        {
            int variable2;
            stream >> variable2;
            Element elem;
            elem.key=value;
            elem.value=variable2;
            insertElem(list[currentL],elem);
            continue;
        }

        if(isCommand(command,"GO"))
        {
            list=new List2W[value];
            continue;
        }

        if(isCommand(command,"AD"))
        {
            addList(list[currentL],list[value]);
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
