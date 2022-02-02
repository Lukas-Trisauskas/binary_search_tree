#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <numeric>

struct transaction
{
public:
    int id;
    const std::string desc;
    std::string timestamp;
    int value;
    transaction(int id, std::string desc, std::string timestamp, int value) : id(id), desc(desc), timestamp(timestamp), value(value) {
    };
    ~transaction() {};
    void toString();
};
std::string getDateTime() {
    time_t raw_time;
    time(&raw_time);
    return ctime(&raw_time);
}
void transaction::toString() 
{
    printf("[%i] --%s: %c%i on %s\n", id, desc.c_str(), char(156), value, timestamp.c_str());
}
//node structure
struct Node
{
    int key;
    Node* left;
    Node* right;
    transaction* data;
    ~Node() {};
    Node(int key, transaction* data) : key(key), left(nullptr), right(nullptr), data(data) {};
};
class BinarySearchTree
{
public:
    Node* root; 
    BinarySearchTree() {
        root = nullptr;
    };
    ~BinarySearchTree() {};
    int returnNode(int id, Node* ptr);
    void insertNode(int id, Node* ptr, transaction* data);
    void build(std::vector<transaction*> history, BinarySearchTree tree);
    void returnData(int value, Node* ptr);
    void preOrderTraversal(Node* ptr);

    
};
/*
void BinarySearchTree::insertNode(int key, node* ptr)
{
    //check if the tree is empty
    if (root == NULL)
    {
        //if the tree is empty create a new node
        //make the root pointer point to that newly created node
        root = new node(key);
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
            insertNode(key, ptr->left);
        }
        else
        {   //if left pointer of root node is not pointing to anything then,
            //make left of root node, point to a new node.
            ptr->left = new node(key);
            
        }
    }
    //same process as above, but for the right subtree.
    else if (key > ptr->key)
    {
        if (ptr->right != NULL)
        {
            insertNode(key, ptr->right);
        }
        else
        {
            ptr->right = new node(key);
        }
    }
    //if the key is equal to the pointer key
    else
    {
        std::cout << "The key " << key << " has already been added to the tree\n";
    }
};
*/
int BinarySearchTree::returnNode(int key, Node* ptr)
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
};
void BinarySearchTree::insertNode(int key, Node* ptr, transaction* data)
{
    //check if the tree is empty
    if (root == NULL)
    {
        //if the tree is empty create a new node
        //make the root pointer point to that newly created node
        root = new Node(key, data);
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
            ptr->left = new Node(key, data);

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
            ptr->right = new Node(key, data);
        }
    }
    //if the key is equal to the pointer key
    else
    {
        std::cout << "The key " << key << " has already been added to the tree\n";
    }
}
void BinarySearchTree::returnData(int id, Node* ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    else
    {
        if (ptr != NULL)
        {
            if (ptr->data->value == id)
            {
                ptr->data->toString();
            }
            else
            {
                if (id < ptr->data->value)
                {
                    return returnData(id, ptr->left);
                }
                else
                {
                    return returnData(id, ptr->right);
                }
            }
        }
        else
        {
            std::cout << "dsfsd";
        }
    }
    returnData(id, ptr->left);
    returnData(id, ptr->right);
};


void BinarySearchTree::preOrderTraversal(Node* ptr)
{
    if (root == nullptr)
    {
        return;
    }
    std::cout << ptr->key << " ";
    preOrderTraversal(ptr->left);
    preOrderTraversal(ptr->right);
};          
int reorder(std::vector<transaction*>& keys, std::vector<int>& btree, int start, int end)
{
    //using divide an conquer method to obtain the median of value of the array and recursively repeat the process on a subvector
    //to convert oredered vector to a bst.
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    reorder(keys, btree, start, mid - 1);
    reorder(keys, btree, mid + 1, end);
    btree.push_back(keys[mid]->id);
    return keys[mid]->id;
};
void build(std::vector<transaction*>& history, BinarySearchTree& tree)
{
    std::vector<int> btree; //balanced tree is stored here
    reorder(history, btree, 0, history.size() - 1);

    // solution to reverse iterate through a vector
    std::vector<int>::reverse_iterator i;
    for (i = btree.rbegin(); i < btree.rend(); i++)
    {
        //history.at(*i - 1)->toString();
        tree.insertNode(*i, tree.root, history[*i - 1]);
    }

};

int main()
{   
    int key = 0;
    std::vector<transaction*> history;
    history.push_back(new transaction(++key, "1withdraw", getDateTime(), 10));
    history.push_back(new transaction(++key, "2withdraw", getDateTime(), 20));
    history.push_back(new transaction(++key, "3deposit", getDateTime(), 30));
    history.push_back(new transaction(++key, "4withdraw", getDateTime(), 40));
    history.push_back(new transaction(++key, "5deposit", getDateTime(), 40));
    history.push_back(new transaction(++key, "withdraw", getDateTime(), 40));
    
    BinarySearchTree tree;
    build(history, tree);
    tree.returnData(40, tree.root);
};
