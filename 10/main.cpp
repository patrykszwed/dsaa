#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Elem{
    double weight;
};

struct Graph{
    int v;  //v - total number of vertices
    Elem **arr;
};

void loadGraph(Graph &g, int n, int m){
    g.v = n;
    g.arr = new Elem*[n];
    for(int i = 0 ; i < n; ++i)
        g.arr[i] = new Elem[n];

    int vertexIndex;
    int endingVertexIndex;
    double nodeWeight;

    for(int i = 0; i < n; ++i){ //set the values of an array
        for(int j = 0 ; j < n; ++j){
            if(i == j)
                g.arr[i][j].weight = 0;
            else{
                g.arr[i][j].weight = INFINITY;
            }
        }
    }

    int i = 0;

    while (i < m) {
        cin >> vertexIndex;    //load vertex
        cin >> endingVertexIndex; //load endingVertex
        cin >> nodeWeight;  //load weight

        g.arr[vertexIndex][endingVertexIndex].weight = nodeWeight;

        ++i;
    }
}

void insertEdge(Graph &g, int u, int v, double weight){
    if(u > g.v) //check if u is a correct value
        return;
    g.arr[u][v].weight = weight;
}

bool findEdge(Graph &g, int u, int v, double &weight){
    if(g.arr[u][v].weight != INFINITY) {
        weight = g.arr[u][v].weight;
        return true;
    }
    return false;
}

void showAsMatrix(Graph &g){
    for(int i = 0; i < g.v; ++i){
        for(int j = 0 ; j < g.v; ++j){
            if(g.arr[i][j].weight == INFINITY)
                cout << "-,";
            else{
                cout << g.arr[i][j].weight << ",";
            }
        }
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for(int i = 0; i < g.v; ++i){
        cout << i << ":";
        for(int j = 0; j < g.v; ++j){
            if(g.arr[i][j].weight != INFINITY && g.arr[i][j].weight != 0)
                cout << j << "(" << g.arr[i][j].weight << ")" << ",";
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
