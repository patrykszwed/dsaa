#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Heap{
    int *arr;
    int size;
    int pos;
    bool isSorted;
};

void init(Heap& h, int size){
    h.arr = new int[size];
    h.size = size;
    h.pos = 0;
}

void heapify(Heap &h, int idx){
    int n = h.pos;
    int idxOfBigger = 2 * idx + 1;
    if(idxOfBigger < n){
        if(idxOfBigger + 1 < n && h.arr[idxOfBigger] < h.arr[idxOfBigger+1])
            idxOfBigger++;
        if(h.arr[idx] < h.arr[idxOfBigger]){
            swap(h.arr[idx], h.arr[idxOfBigger]);
            heapify(h, idxOfBigger);
        }
    }
}

void heapifyForSorting(Heap &h, int idx, int n){
    int idxOfBigger = 2 * idx + 1;
    if(idxOfBigger < n){
        if(idxOfBigger + 1 < n && h.arr[idxOfBigger] < h.arr[idxOfBigger+1])
            idxOfBigger++;
        if(h.arr[idx] < h.arr[idxOfBigger]){
            swap(h.arr[idx], h.arr[idxOfBigger]);
            heapifyForSorting(h, idxOfBigger, n);
        }
    }
}

void heapAdjustment(Heap &h){
    for(int i = (h.pos-1)/2; i >= 0; --i)
        heapify(h, i);
}

void loadAndMakeHeap(Heap &h, int howMany){
    for(int i = 0; i < howMany; ++i) {
        if(h.pos >= h.size)   //check if there's a space left for the next number
            break;
        cin >> h.arr[h.pos++];
    }

    heapAdjustment(h);
}

/*void add(Heap &h, int value){
    if(h.isSorted)
        return;
    if(h.pos < h.size){ //if there's no space for another number, do nothing
        h.arr[h.pos++] = value;
        heapAdjustment(h);
    }
}*/

int getParent(int idx){
    int result = (idx - 1) / 2;
    return result;
}

void swapAndClimb(int *tab, int parent, int node){
    /*if(tab[parent] < tab[node])
        swap(tab[parent], tab[node]);
    if(parent != 0 && parent > getParent(parent))
            swapAndClimb(tab, getParent(parent), parent);*/
    swap(tab[parent], tab[node]);
    if(parent != 0 && tab[parent] > tab[getParent(parent)])
        swapAndClimb(tab, getParent(parent), parent);
}

void add(Heap &h, int value){
    if(h.isSorted)
        return;

    if(h.pos < h.size)
        h.arr[h.pos]=value;

    if(h.arr[h.pos] > h.arr[getParent(h.pos)])
        swapAndClimb(h.arr, getParent(h.pos), h.pos);

    ++h.pos;
}

void makeSorted(Heap& h){
    h.isSorted = true;
    heapAdjustment(h);
    for(int i = h.pos - 1; i > 0; --i){
        swap(h.arr[i], h.arr[0]);
        heapifyForSorting(h, 0, i);
    }
}

void siftUp(int nodeIndex, Heap &h){
    int parentIndex;
    if(nodeIndex != 0){
        parentIndex = (nodeIndex - 1) / 2;
        if(h.arr[parentIndex] > h.arr[nodeIndex]){
            swap(h.arr[parentIndex], h.arr[nodeIndex]);
            siftUp(parentIndex, h);
        }
    }
    //makeSorted(h);
}

void addNew(Heap &h, int value){
    if(h.pos < h.size){
        h.arr[h.pos++] = value;
        siftUp(h.pos, h);
    }
}

void show(Heap& h){
    for(int i = 0; i < h.pos; ++i)
        cout << h.arr[i] << ",";
    cout << endl;
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
    Heap *heap;
    int currentH=0;
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
            show(heap[currentH]);
            continue;
        }

        if(isCommand(command,"MS")) //*
        {
            makeSorted(heap[currentH]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"IN")) //*
        {
            init(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"LD"))
        {
            loadAndMakeHeap(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"AD"))
        {
            add(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"AN"))
        {
            addNew(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"CH"))
        {
            currentH=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            heap=new Heap[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
