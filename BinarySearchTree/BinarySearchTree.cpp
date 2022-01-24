#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <chrono>
#include <time.h>


std::string getDateTime()
{
    time_t raw_time;
    time(&raw_time);
    return ctime(&raw_time);
};
struct transaction
{
public:
    int transaction_id;
    std::string desc;
    std::string timestamp;
    int value;
    transaction(int id, std::string desc, std::string timestamp, int value);
    ~transaction();
    void toString();
};
transaction::transaction(int id, std::string d, std::string t, int v)
{
    transaction_id = id;
    desc = d;
    timestamp = t;
    value = v;
}
transaction::~transaction()
{

};
void transaction::toString() 
{
    printf("--%s: %c%i on %s\n", desc.c_str(), char(156), value, timestamp.c_str());
}
//node structure
struct node
{
    int key;
    node* left;
    node* right;
    transaction* data;
    ~node();
};
node::~node()
{
    delete left;
    delete right;
    delete data;
}
class BinarySearchTree
{
public:
    node* root;
public:
    BinarySearchTree();
    ~BinarySearchTree() {
        delete root;
    }
    node* createNode(int key, transaction* data);
    void insertNode(int key, node* ptr, transaction* data);
    void printInOrder(node* ptr);
    int returnNode(int key, node* ptr);
    void returnData(int id, node* ptr);
    void rotateLeft(int key, node* ptr);
};
BinarySearchTree::BinarySearchTree()
{
    //make sure that the root doesn't point to anything at the start
    root = NULL;
}
//function that creates and returns a new node (leaf)
node* BinarySearchTree::createNode(int key, transaction* data)
{
    node* n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->data = data;
    //note: it's called a leaf because it doesn't point to anything
    return n;
}
void BinarySearchTree::insertNode(int key, node* ptr, transaction* data)
{
    //check if the tree is empty
    if (root == NULL)
    {
        //if the tree is empty create a new node
        //make the root pointer point to that newly created node
        root = createNode(key, data);
    }
    //if the root is pointing to a node then,
    //check if the key value that we want to add is less than,
    //the key value of the node pointed by the root.
    else if (key < ptr->key)
    {
        //if the key value is less than the root node key value then,
        //check if the left subtree is not empty.
        if (ptr->left != NULL)
        {
            //if the left subtree is not empty, call the insertNode (recursively),
            //and traverse down the left subtree.
            insertNode(key, ptr->left, data);
        }
        else
        {   //if left pointer of root node is not pointing to anything then,
            //make left of root node, point to a new node.
            ptr->left = createNode(key, data);
        }
    }
    //same process as above, but for the right subtree.
    else if (key > ptr->key)
    {
        if (ptr->right != NULL)
        {
            insertNode(key, ptr->right, data);
        }
        else
        {
            ptr->right = createNode(key, data);
        }
    }
    //if the key is equal to the pointer key
    else
    {
        std::cout << "The key " << key << " has already been added to the tree\n";
    }
}
//recursively traverses the tree from lowest value to highest value
void BinarySearchTree::printInOrder(node* ptr)
{
    if (root != NULL)
    {
        if (ptr->left != NULL)
        {
            printInOrder(ptr->left);
        }
        std::cout << ptr->key << " ";
        if (ptr->right != NULL)
        {
            printInOrder(ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty\n";
    }
}
int BinarySearchTree::returnNode(int key, node* ptr)
{
    if (root != NULL)
    {
        if (ptr->key == key)
        {
            return ptr->key;
        }
        else
        {
            if (key < ptr->key)
            {
                return returnNode(key, ptr->left);
            }
            else
            {
                return returnNode(key, ptr->right);
            }
        }
    }
    else
    {
        return NULL;
    }
}
void BinarySearchTree::returnData(int id, node* ptr)
{
    if (root != NULL)
    {
        if (ptr->key == id)
        {
            return ptr->data->toString();
        }
        else
        {
            if (id < ptr->key)
            {
                returnData(id, ptr->left);
            }
            else
            {
                returnData(id, ptr->right);
            }
        }
    }
    else
    {
        std::cout << "transaction not found\n";
    }
};


int main()
{
    /*
    int B[10] = { 20, 62, 48, 38, 5, 9, 94, 65, 12, 36 };
    BinarySearchTree myTree;

    for (auto i : B)
    {
        myTree.insertNode(i, myTree.root);
    }
    myTree.printInOrder(myTree.root);
    std::cout << "\n";
    int key = myTree.returnNode(20, myTree.root);
    */


    transaction* ptr = nullptr;
    std::vector<transaction*> history;
    history.push_back(new transaction(5, "deposit", getDateTime(), 1500));
    history.push_back(new transaction(1, "withdraw", getDateTime(), 100));
    history.push_back(new transaction(6,"withdraw", getDateTime(), 50));
    history.push_back(new transaction(2,"withdraw", getDateTime(), 200));
    history.push_back(new transaction(9, "withdraw", getDateTime(), 150));
    history.push_back(new transaction(20, "transfer", getDateTime(), 100));
    history.push_back(new transaction(4, "deposit", getDateTime(), 100));

    BinarySearchTree myTree;

    for (int i = 0; i < history.size(); i++)
    {   
        myTree.insertNode(history[i]->transaction_id, myTree.root, history[i]);
    }
    myTree.returnData(4, myTree.root);
}

