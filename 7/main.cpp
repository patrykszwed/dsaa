#include<iostream>
#include <string>
#include <sstream>

// BST

using namespace std;


struct Element{
    int key;
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

void init(BST & tree){
    tree.root = new Node;
    tree.root->parent = NULL;
    tree.root->left = NULL;
    tree.root->right = NULL;
    tree.root = NULL;
}

void countLeaves(Node *node, int &x){
    if (!node){
        return;
    }
    if(node->left == NULL && node->right == NULL )
        ++x;

    // first recur on left subtree
    countLeaves(node->left, x);

    // then recur on right subtree
    countLeaves(node->right, x);
}

int countLeaves(BST & tree){
    int result = 0;
    countLeaves(tree.root, result);
    return result;
}

Node * newNode(Element elem){
    Node *newNode = new Node;
    newNode->elem = elem;
    newNode->left = newNode->right = NULL;
    return newNode;
}

bool insertElem(BST & tree, Element elem){
    if(!tree.root) {
        tree.root = newNode(elem);
        tree.root->parent = NULL;
        return true;
    }
    else{
        Node **p = &tree.root;
        Node **prev = p;
        while(*p){
            if(elem.key < (*p)->elem.key) {
                prev = p;
                p = &(*p)->left;
                continue;
            }
            if(elem.key > (*p)->elem.key) {
                prev = p;
                p = &(*p)->right;
                continue;
            }
            if(elem.key == (*p)->elem.key)
                return false;
        }
        *p = newNode(elem);
        if((*p)->elem.key > (*prev)->elem.key)
            (*prev)->right = *p;
        else
            (*prev)->left = *p;
        (*p)->parent = (*prev);

        return true;
    }
}

void showInorder(Node * node){
    if(!node)
        return;

    showInorder(node->left);
    cout << node->elem.key << "(" << node->elem.value << "),";
    showInorder(node->right);
}

void showInorder(BST & tree){
    showInorder(tree.root);
    cout << endl;
}

void showPreorder(Node * node){
    if (!node)
        return;

    // first print data of node
    cout << node->elem.key << "(" << node->elem.value << "),";

    // then recur on left subtree
    showPreorder(node->left);

    // now recur on right subtree
    showPreorder(node->right);
}

void showPostorder(Node * node){
    if (!node)
        return;

    // first recur on left subtree
    showPostorder(node->left);

    // then recur on right subtree
    showPostorder(node->right);

    // now deal with the node
    cout << node->elem.key << "(" << node->elem.value << "),";
}

void showPreorder(BST & tree){
    showPreorder(tree.root);
    cout << endl;
}

void showPostorder(BST & tree){
    showPostorder(tree.root);
    cout << endl;
}

Node *findNode(Node *node,int key){
    return NULL;
}



bool findKey(BST & tree,int key, Element &elem){
    if(tree.root == NULL)   //binary tree is empty
        return false;

    if(tree.root->elem.key == key){
        elem = tree.root->elem;
        return true;
    }

    Node *p = tree.root;

    while(p != NULL){
        if(p->elem.key < key){
            p = p->right;
            continue;
        }
        if(p->elem.key > key){
            p = p->left;
            continue;
        }
        if(p->elem.key == key){
            elem = p->elem;
            return true;
        }
    }
    return false;
}

Node *minimalNode(Node *node){
    Node *p = node;

    while(p->left != NULL)
        p = p->left;

    return p;
}

void clear(Node *node);

Node* deleteNode(Node* node, BST &tree)
{
    if(node->right == NULL && node->left == NULL && node->parent != NULL){ //no children
        if(node->elem.key > node->parent->elem.key) //remove parent's pointer
            node->parent->right = NULL;
        else if(node->elem.key < node->parent->elem.key)
            node->parent->left = NULL;
        else if(node->elem.key == node->parent->elem.key) {   //case when you remove duplicate
            if(node->parent->right)
                node->parent->right = NULL;
            else
                node->parent->left = NULL;
        }
        node->parent = NULL;
        delete node;
        return NULL;
    }
        // node with only one child
    else if (node->left == NULL && node->right != NULL) {
        Node *temp = node->right;
        if(node->parent) {
            temp->parent = node->parent;
            if(temp->elem.key > node->parent->elem.key) //compare keys
                node->parent->right = temp;
            else
                node->parent->left = temp;
        }
        else {    //that's root
            node->elem = temp->elem;
            deleteNode(node->right,tree);
            return node;
        }
        node->parent = NULL;
        node->right = NULL;
        delete node;
        return temp;
    }
    else if (node->right == NULL && node->left != NULL) {
        Node *temp = node->left;
        if(node->parent) {
            temp->parent = node->parent;
            node->parent->left = temp;
        }
        else {    //that's root
            node->elem = temp->elem;
            deleteNode(node->left, tree);
            return node;
        }
        node->parent = NULL;
        node->left = NULL;
        delete node;
        return temp;
    }
    else if(node->right == NULL && node->left == NULL && node->parent == NULL){ //no children + this is root
        tree.root = NULL;
        clear(node);
        return NULL;
    }

    // node with two children: Get the inorder successor (smallest
    // in the right subtree)
    Node* temp = minimalNode(node->right);

    // Copy the inorder successor's content to this node
    node->elem = temp->elem;

    // Delete the inorder successor
    deleteNode(temp, tree);

    return node;
}

bool removeKey(BST & tree, int key, Element &elem){
    if(!tree.root)  //empty tree
        return false;

    Node *ptr = tree.root;

    while(ptr){
        if(ptr->elem.key == key){
            elem = ptr->elem;
            deleteNode(ptr, tree);
            return true;
        }

        if(ptr->elem.key < key){
            ptr = ptr->right;
            continue;
        }

        if(ptr->elem.key > key){
            ptr = ptr->left;
            continue;
        }
    }

    return false;
}

void clear(Node *node){
    if(!node)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

void clear(BST & tree){
    clear(tree.root);
    tree.root = NULL;
}

void countNodes(Node *node, int &x){
    if (node == NULL)
        return;

    ++x;

    // first recur on left subtree
    countNodes(node->left, x);

    // then recur on right subtree
    countNodes(node->right, x);
}

int numberOfNodes(BST & tree){
    int result = 0;
    countNodes(tree.root, result);
    return result;
}

int height(Node *node){
    if(!node)
        return 0;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    if(leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int height(BST & tree){
    if(!tree.root)
        return 0;

    int result = height(tree.root);
    return result;
}

int functionA(BST & tree){
    return -1;
}

int functionB(BST & tree, int key){
    return -1;
}

bool functionC(BST & tree, int key, Element &elem){
    return false;
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
    BST *tree;
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

        if(isCommand(command,"SI"))
        {
            showInorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SP"))
        {
            showPreorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SQ"))
        {
            showPostorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"CL"))
        {
            clear(tree[currentT]);
            continue;
        }

        if(isCommand(command,"IN"))
        {
            init(tree[currentT]);
            continue;
        }

        if(isCommand(command,"NN"))
        {
            cout << numberOfNodes(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"HE"))
        {
            cout << height(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"FA"))
        {
            cout << functionA(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"LE"))
        {
            cout << countLeaves(tree[currentT]) << endl;
            continue;
        }

        // read next argument, one int value
        stream >> value;


        if(isCommand(command,"IE"))
        {
            int variable2;
            stream >> variable2;
            Element elem;
            elem.key=value;
            elem.value=variable2;
            showBool(insertElem(tree[currentT],elem));
            continue;
        }

        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        if(isCommand(command,"RK"))
        {
            Element elem;
            bool ret=removeKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
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
            tree=new BST[value];
            continue;
        }

        if(isCommand(command,"FB"))
        {
            cout << functionB(tree[currentT],value) << endl;
            continue;
        }

        if(isCommand(command,"FC"))
        {
            Element elem;
            bool ret=functionC(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        cout << "wrong argument in test: " << command << endl;

    }
    return 0;
}
