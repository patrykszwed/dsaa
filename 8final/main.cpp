//
// Created by Patryk on 5/6/2018.
//

#include <sstream>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <ctime>
#include <unordered_map>
#include <vector>

// BST

using namespace std;


struct Element{
    string key;
    int value;
};

struct Node{
    Element elem;
    Node *left; //left child
    Node *right; //right child
    Node *parent;
};

// Binary search tree
struct BST{
    Node *root;
};

Element *mostOften[10]; //10 most popular words

Node * newNode(string word){
    Node *newNode = new Node;
    newNode->elem.key = word;
    newNode->elem.value = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

long double countSeconds( clock_t time )
{
    return static_cast < long double >( time ) / CLOCKS_PER_SEC;
}

void fixArray(Element &elem){
    int i;
    for (i=0; mostOften[i] != &elem && i < 9; ++i);

    if (i==0)
        return;

    if (mostOften[i] != &elem)
        mostOften[9] = &elem;

    while(mostOften[i]->value > mostOften[i-1]->value){
        Element *buff = mostOften[i];
        mostOften[i] = mostOften[i-1];
        mostOften[i-1] = buff;
        --i;

        if(i==0)
            break;
    }
}

void insertWord(BST & tree, string word){
    if(!tree.root) {
        tree.root = newNode(word);
        tree.root->parent = NULL;
        return;
    }
    else{
        Node **p = &tree.root;
        Node **prev = p;
        while(*p){
            if(word < (*p)->elem.key) {
                prev = p;
                p = &(*p)->left;
                continue;
            }
            if(word > (*p)->elem.key) {
                prev = p;
                p = &(*p)->right;
                continue;
            }
            if (word == (*p)->elem.key) {
                ++(*p)->elem.value;
                if((*p)->elem.value > mostOften[9]->value)
                    fixArray((*p)->elem);
                return;
            }
        }
        *p = newNode(word);
        if((*p)->elem.key > (*prev)->elem.key)
            (*prev)->right = *p;
        else
            (*prev)->left = *p;
        (*p)->parent = (*prev);

        return;
    }
}

//vector<std::pair<std::string,int>> mostOftenPair(10); //wersja bez potrzeby inicjalizacji w petli
pair<string, int> mostOftenPair[10];

void fixArray (pair<string, int> p){
    int i;
    for (i=0; mostOftenPair[i].first != p.first && i<9; ++i);
    if (i==0){
        mostOftenPair[0] = p;
        return;
    }
    if (mostOftenPair[i].first != p.first)
        mostOftenPair[9] = p;
    else
        mostOftenPair[i] = p;
    while(mostOftenPair[i].second > mostOftenPair[i-1].second){
        pair <string, int> buff = mostOftenPair[i];
        mostOftenPair[i] = mostOftenPair[i-1];
        mostOftenPair[i-1] = buff;
        --i;
        if(i==0)
            break;
    }
}

void bbst(string filename) {
    map <string, int> arr;

    for (int i = 0; i < 10; ++i)
        mostOftenPair[i] = make_pair (std::string(), 0);

    ifstream file;

    file.open(filename);

    if(file.is_open()) {
        string loadLine;
        string word;
        clock_t start = clock();

        while (!file.eof()){
            getline(file, loadLine);
            for(int i = 0; i < loadLine.length() + 1; ++i){
                if(!isalpha(loadLine[i])){  //end of a word
                    if(!word.empty()){
                        ++arr[word];
                        if(arr[word] > mostOftenPair[9].second)
                            fixArray(make_pair(word, arr[word]));
                        word = "";
                    }
                }
                else
                    word += std::to_string(tolower(loadLine[i]));
            }
        }

        clock_t value = clock() - start;


        for(int i = 0; i < 10; ++i)
            cout << mostOftenPair[i].first << " - " << mostOftenPair[i].second << endl;

        cout << "Execution time: " << countSeconds(value) << " seconds. (BBST)\n\n";
    }
    else
        cout << "There is no such file.";

    file.close();

}

pair <string, int> mostOftenUnorderedPair[10];

void fixArrayUnorderedMap (pair<string, int> p){
    int i;
    for (i=0; mostOftenUnorderedPair[i].first != p.first && i<9; ++i);
    if (i==0){
        mostOftenUnorderedPair[0] = p;
        return;
    }
    if (mostOftenUnorderedPair[i].first != p.first)
        mostOftenUnorderedPair[9] = p;
    else
        mostOftenUnorderedPair[i] = p;
    while(mostOftenUnorderedPair[i].second > mostOftenUnorderedPair[i-1].second){
        pair <string, int> buff = mostOftenUnorderedPair[i];
        mostOftenUnorderedPair[i] = mostOftenUnorderedPair[i-1];
        mostOftenUnorderedPair[i-1] = buff;
        --i;
        if(i==0)
            break;
    }
}

void hashtable(const string &filename) {
    unordered_map <string, int> arr;

    for (short i=0; i<10; ++i)
        mostOftenUnorderedPair[i] = make_pair (string(), 0);

    ifstream file;

    file.open(filename);

    if(file.is_open()) {
        string loadLine;
        string word;
        clock_t start = clock();

        while (!file.eof()){
            getline(file, loadLine);
            for(int i = 0; i < loadLine.length() + 1; ++i){
                if(!isalpha(loadLine[i])){  //end of a word
                    if(!word.empty()){
                        ++arr[word];
                        if(arr[word] > mostOftenPair[9].second)
                            fixArrayUnorderedMap(make_pair(word, arr[word]));
                        word = "";
                    }
                }
                else
                    word += std::to_string(tolower(loadLine[i]));
            }
        }

        clock_t value = clock() - start;


        for(int i = 0; i < 10; ++i)
            cout << mostOftenPair[i].first << " - " << mostOftenPair[i].second << endl;

        cout << "Execution time: " << countSeconds(value) << " seconds. (Hash Table)\n\n";
    }
    else
        cout << "There is no such file.";

    file.close();

}


int main() {

    for(int i = 0; i < 10; ++i){    //initialize the mostOften array
        mostOften[i] = new Element;
        mostOften[i]->key = "";
        mostOften[i]->value = 0;
    }

    string filename;

    cout << "Give the name of the file:\n";
    cin >> filename;
    cout << endl;

    ifstream file;

    string txt = ".txt";

    filename.append(txt);

    file.open(filename);

    if(file.is_open()) {
        auto *tree = new BST;
        string loadLine;
        string word;
        clock_t start = clock();

        while (!file.eof()){
            getline(file, loadLine);
            for(int i = 0; i < loadLine.length() + 1; ++i){
                if(!isalpha(loadLine[i])){  //end of a word
                    if(!word.empty()){
                        insertWord(*tree, word);
                        word = "";
                    }
                }
                else
                    word += tolower(loadLine[i]);
            }
        }

        clock_t value = clock() - start;


        for(int i = 0; i < 10; ++i)
            cout << mostOften[i]->key << " - " << mostOften[i]->value << endl;

        cout << "Execution time: " << countSeconds(value) << " seconds. (BST)\n\n";
    }
    else
        cout << "There is no such file.";

    file.close();

    bbst(filename);
    hashtable(filename);

    return 0;
}
