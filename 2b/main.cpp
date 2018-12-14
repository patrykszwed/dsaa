// 2bvs.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element
{
    int key;
    Element *next;
};

struct List
{
    Element *head;
};

void init(List& l)
{
    l.head = NULL;
}


void insertHead(List& l, int x)
{
    Element *newEl = new Element;
    newEl->key = x;
    newEl->next = l.head;
    l.head = newEl; //set head to point on the new element
}

bool deleteHead(List& l, int &oldHead)
{
    if (l.head != NULL)
    {
        Element *p = l.head;
        oldHead = p->key;
        l.head = p->next;
        delete p;
        return true;
    }
    return false;
}

void insertTail(List& l, int x)
{
    Element *newEl = new Element;
    newEl->key = x;
    newEl->next = NULL;

    Element *p = l.head;
    if(p == NULL)
    {
        l.head = newEl;
        return;
    }
    while(p->next != NULL)
    {
        p = p->next;  //go to the last element
    }
    p->next = newEl;    //if that was the last element, set the pointer to the new tail
}

bool deleteTail(List& l, int &oldTail)
{
    if(l.head != NULL)
    {
        Element *p = l.head;
        if(p->next != NULL)
        {
            while(p->next->next != NULL)
            {
                p = p->next;
            }
            oldTail = p->next->key;
            p->next = NULL;
        }
        else if(p->next == NULL)    //there's only 1 element
        {
            oldTail = p->key;
            l.head = NULL;
        }
        return true;
    }
    return false;
}

int findPosOfValue(List& l, int value)
{
    int index = 0;
    Element *p = l.head;
    while (p != NULL && p->key != value)
    {
        p = p->next;
        index++;
    }
    if (p == NULL)
        return -1;
    return index;
}

bool deleteValue(List& l, int value)
{
    if (l.head != NULL)
    {
        if (l.head->key == value)
        {
            int tmp;    //tmp variable for deleteHead function
            deleteHead(l, tmp);
            return true;
        }
        else
        {
            Element *p = l.head;
            while (p->next != NULL)
            {
                if(p->next->key == value)
                {
                    p->next = p->next->next;
                    return true;
                }
                p = p->next;
            }
        }
    }
    return false;
}

bool atPosition(List& l, int pos, int &value)
{
    if (l.head != NULL)
    {
        Element *p = l.head;
        for (int i = 0; i < pos; ++i)
        {
            if (p == NULL)   //if the position is out of the range of the list return false
                return false;
            p = p->next;
        }
        value = p->key;
        return true;
    }
    return false;
}

bool deleteSecond(List &l, int &oldValue)
{
    if(l.head != NULL && l.head->next != NULL)
    {
        Element *ptr = l.head->next;
        oldValue = ptr->key;
        l.head->next = l.head->next->next;  //set header's next to point to the 3rd element

        //Element *p = l.head->next;

        delete ptr;
        return true;
    }
    return false;
}

void showListFromHead(List& l)
{
    if (l.head != NULL)
    {
        Element *p = l.head;
        cout << p->key << ",";
        while (p->next != NULL)
        {
            cout << p->next->key << ",";
            p = p->next;
        }
    }
    cout << endl;
}

void clearList(List& l)
{
    int tmp; //temporary variable
    while (deleteHead(l, tmp));
}

void showBool(bool val)
{
    if (val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}


bool isCommand(const string command, const char *mnemonic)
{
    return command == mnemonic;
}

int main()
{
    string line;
    string command;
    List *list = NULL;
    int currentL = 0;
    int value;
    cout << "START" << endl;
    while (true)
    {
        getline(cin, line);
        std::stringstream stream(line);
        stream >> command;
        if (line == "" || command[0] == '#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0] = toupper(command[0]);
        command[1] = toupper(command[1]);

        if (isCommand(command, "HA"))
        {
            cout << "END OF EXECUTION" << endl;
            break;
        }


        // zero-argument command
        if (isCommand(command, "DH"))
        {
            int retValue;
            bool retBool = deleteHead(list[currentL], retValue);
            if (retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        if (isCommand(command, "DT"))
        {
            int retValue;
            bool retBool = deleteTail(list[currentL], retValue);
            if (retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }

        if (isCommand(command, "SH"))
        {
            showListFromHead(list[currentL]);
            continue;
        }

        if (isCommand(command, "CL"))
        {
            clearList(list[currentL]);
            continue;
        }

        if (isCommand(command, "IN"))
        {
            init(list[currentL]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if (isCommand(command, "FP"))
        {
            int ret;
            ret = findPosOfValue(list[currentL], value);
            cout << ret << endl;
            continue;
        }

        if (isCommand(command, "DV"))
        {
            showBool(deleteValue(list[currentL], value));
            continue;
        }

        if (isCommand(command, "DS"))
        {
            showBool(deleteSecond(list[currentL], value));
            continue;
        }


        if (isCommand(command, "AT"))
        {
            int retValue;
            bool retBool = atPosition(list[currentL], value, retValue);
            if (retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }

        if (isCommand(command, "CH"))
        {
            currentL = value;
            continue;
        }

        if (isCommand(command, "IH"))
        {
            insertHead(list[currentL], value);
            continue;
        }

        if (isCommand(command, "IT"))
        {
            insertTail(list[currentL], value);
            continue;
        }

        if (isCommand(command, "GO"))
        {
            list = new List[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
}

