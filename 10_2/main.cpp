#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct adjListNode{
    adjListNode *next, *prev;
    int id;
    double weight;
};

struct adjList{
    adjListNode *head;
};

struct Graph{
    int v;  //v - total number of vertices
    adjList *adjArr;
};

void sortList(Graph &g, int vertexIndex, adjListNode *newEl) {
    if (g.adjArr[vertexIndex].head == NULL) {    //the list is empty
        newEl->prev = newEl;
        newEl->next = NULL;
        g.adjArr[vertexIndex].head = newEl;
    } else {
        adjListNode *p = g.adjArr[vertexIndex].head;
        adjListNode *ptr = p;  //store element behind p
        while (ptr->id <= newEl->id && p != NULL) {
            if (ptr->id == newEl->id) {
                ptr->weight = newEl->weight;
                return;
            }
            ptr = p;
            p = p->next;
        }
        if (ptr->id == newEl->id) {
            ptr->weight = newEl->weight;
            return;
        }
        if (p == NULL) {
            if(ptr->id > newEl->id){
                newEl->next = ptr;
                ptr->prev = newEl;
                g.adjArr[vertexIndex].head = newEl;
                g.adjArr[vertexIndex].head->prev = ptr;
                ptr->next = NULL;
                return;
            }
            newEl->next = NULL;
            newEl->prev = ptr;
            g.adjArr[vertexIndex].head->prev = newEl;
            ptr->next = newEl;
            return;
        }
        else {
            if(ptr->id > newEl->id){
                newEl->next = ptr;
                ptr->prev = newEl;
                p = g.adjArr[vertexIndex].head->prev;
                g.adjArr[vertexIndex].head = newEl;
                g.adjArr[vertexIndex].head->prev = p;
                return;
            }
            newEl->next = NULL;
            newEl->prev = ptr;
            g.adjArr[vertexIndex].head->prev = newEl;
            ptr->next = newEl;
        }
    }
}

void loadGraph(Graph &g, int n, int m){
    g.v = n;

    int vertexIndex;
    int endingVertexIndex;
    double nodeWeight;

    g.adjArr = new adjList[n];
    for(int i = 0; i < n; ++i)
        g.adjArr[i].head = NULL;

    int i = 0;

    while (i < m) {
        cin >> vertexIndex;    //load vertex
        cin >> endingVertexIndex; //load endingVertex
        cin >> nodeWeight;  //load weight
        if(!g.adjArr[vertexIndex].head) {   //if that's the first element of the linked list
            adjListNode *newHead = new adjListNode;
            newHead->prev = newHead;
            newHead->next = NULL;
            newHead->weight = nodeWeight;
            newHead->id = endingVertexIndex;
            g.adjArr[vertexIndex].head = newHead;
        }
        else{
            adjListNode *newEl = new adjListNode;

            newEl->weight = nodeWeight;
            newEl->id = endingVertexIndex;

            sortList(g, vertexIndex, newEl);
        }

        ++i;
    }
}

void insertEdge(Graph &g, int u, int v, double weight){
    if(u > g.v) //check if u is a correct value
        return;

    adjListNode *newEl = new adjListNode;

    newEl->weight = weight;
    newEl->id = v;
    newEl->prev = NULL;
    newEl->next = NULL;

    sortList(g, u, newEl);
    //cout << "g.adjArr[" << u << "].head = " << g.adjArr[u].head; DEBUG
}

bool findEdge(Graph &g, int u, int v, double &weight){
    adjListNode *p = g.adjArr[u].head;
    if(p == NULL)
        return false;
    while(p != NULL){
        if(p->id == v){
            weight = p->weight;
            return true;
        }
        p = p->next;
    }
    return false;
}

void showAsMatrix(Graph &g){
    double weight;
    for(int i = 0; i < g.v; ++i){
        for(int j = 0 ; j < g.v; ++j){
            if(i == j)
                cout << "0,";
            else if(findEdge(g, i, j, weight))
                cout << weight << ",";
            else{
                cout << "-,";
            }
        }
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for(int i = 0; i < g.v; ++i){
        cout << i << ":";
        adjListNode *p = g.adjArr[i].head;
        while(p){
            cout << p->id << "(" << p->weight << ")" << ",";
            p = p->next;
        }
        cout << endl;
    }
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}


int main(){
    string line;
    string command;
    Graph *graph;
    int currentT=0;
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
        // zero-argument command
        if(isCommand(command,"SM"))
        {
            showAsMatrix(graph[currentT]);
            continue;
        }

        if(isCommand(command,"SA"))
        {
            showAsArrayOfLists(graph[currentT]);
            continue;
        }


        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"LG"))
        {
            int m;
            stream >> m;
            loadGraph(graph[currentT],value,m);
            continue;
        }

        if(isCommand(command,"IE"))
        {
            int v;
            double w;
            stream >> v >> w;
            insertEdge(graph[currentT],value,v,w);
            continue;
        }

        if(isCommand(command,"FE"))
        {
            int v;
            stream >> v;
            double w;
            bool ret=findEdge(graph[currentT],value,v,w);

            if(ret)
                cout << w << endl;
            else
                cout << "false" << endl;
            continue;
        }


        if(isCommand(command,"CH"))
        {
            currentT=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            graph=new Graph[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
        return 1;
    }
}
