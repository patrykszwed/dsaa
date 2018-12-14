#include<iostream>
#include<string.h>
#include <sstream>
#include <queue>
#include <list>

using namespace std;

#define INFINITY 10000000

struct Elem{
    double weight;
};

struct adjListNode{
    adjListNode *next, *prev;
    int to;
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
        while (ptr->to <= newEl->to && p != NULL) {
            if (ptr->to == newEl->to) {
                ptr->weight = newEl->weight;
                return;
            }
            ptr = p;
            p = p->next;
        }
        if (ptr->to == newEl->to) {
            ptr->weight = newEl->weight;
            return;
        }
        if (p == NULL) {
            if(ptr->to > newEl->to){
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
            if(ptr->to > newEl->to){
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
            newHead->to = endingVertexIndex;
            g.adjArr[vertexIndex].head = newHead;
        }
        else{
            adjListNode *newEl = new adjListNode;

            newEl->weight = nodeWeight;
            newEl->to = endingVertexIndex;

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
    newEl->to = v;
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
        if(p->to == v){
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
            cout << p->to << "(" << p->weight << ")" << ",";
            p = p->next;
        }
        cout << endl;
    }
}

void BFS(Graph &g, int s){
    string color[g.v];
    int distance[g.v]; //distance from the source to vertex "u"
    int predecessor[g.v]; //predecessor of vertex "u"

    for(int u = 0; u < g.v; ++u){
        if(u == s)
            continue;

        color[u] = "WHITE";
        distance[u] = INFINITY;
        predecessor[u] = INFINITY;
    }
    color[s] = "GREY";
    distance[s] = 0;
    predecessor[s] = INFINITY;

    queue <int> Q;
    Q.push(s);  //Enqueue the source
    adjListNode *p;

    cout << s << ",";

    while(!Q.empty()){
        s = Q.front();
        p = g.adjArr[s].head;
        Q.pop();

        while(p){
            if(color[p->to] == "WHITE") {
                cout << p->to << ",";
                color[p->to] = "GREY";
                distance[p->to] = distance[s] + 1;
                predecessor[p->to] = s;
                Q.push(p->to);
            }
            p = p->next;
        }
        color[s] = "BLACK";
    }
    cout << endl;
}

void DFS_Visit(Graph &g, int s, int *time, int *predecessor, string *color, int &t, int *f){
    color[s] = "GREY";
    t += 1;
    time[s] = t;

    adjListNode *p = g.adjArr[s].head;

    while(p){
        if(color[p->to] == "WHITE") {
            cout << p->to << ",";
            predecessor[p->to] = s;
            DFS_Visit(g, p->to, time, predecessor, color, t, f);
        }
        p = p->next;
    }
    color[s] = "BLACK";
    f[s] = t = t + 1;
}

void DFS(Graph &g, int s){
    string color[g.v];
    int time[g.v]; //distance from the source to vertex "u"
    int predecessor[g.v]; //predecessor of vertex "u"
    int f[g.v];
    int t = 0;

    for(int u = 0; u < g.v; ++u){
        color[u] = "WHITE";
        predecessor[u] = INFINITY;
    }

    for(int i = 0 ; i < g.v; ++i) {
        if (color[i] == "WHITE") {
            cout << s << ",";
            DFS_Visit(g, s, time, predecessor, color, t, f);
        }
        s = i;
    }
    cout << endl;
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

        if(isCommand(command,"BF"))
        {
            BFS(graph[currentT], value);
            continue;
        }

        if(isCommand(command,"DF"))
        {
            DFS(graph[currentT], value);
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
