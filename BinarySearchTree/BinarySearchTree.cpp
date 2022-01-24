#include <iostream>
struct transaction
{
    std::string desc;
    std::string timestamp;
    int value;
};
//node structure
struct node
{
    int key;
    node* left;
    node* right;
};
class BinarySearchTree
{
public:
    node* root;
public:
    BinarySearchTree();
    node* createNode(int key);
    void insertNode(int key, node* ptr);
    void printInOrder(node* ptr);
    int returnNode(int key, node* ptr);
};
BinarySearchTree::BinarySearchTree()
{
    //make sure that the root doesn't point to anything at the start
    root = NULL;
}
//function that creates and returns a new node (leaf)
node* BinarySearchTree::createNode(int key)
{
    node* n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    //note: it's called a leaf because it doesn't point to anything
    return n;
}
void BinarySearchTree::insertNode(int key, node* ptr)
{
    //check if the tree is empty
    if (root == NULL)
    {
        //if the tree is empty create a new node
        //make the root pointer point to that newly created node
        root = createNode(key);
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
            ptr->left = createNode(key);
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
            ptr->right = createNode(key);
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
int main()
{
    int B[10] = { 20, 62, 48, 38, 5, 9, 94, 65, 12, 36 };
    BinarySearchTree myTree;

    for (auto i : B)
    {
        myTree.insertNode(i, myTree.root);
    }
    myTree.printInOrder(myTree.root);
    std::cout << "\n";
    int key = myTree.returnNode(20, myTree.root);
    if (key != NULL)
    {
        std::cout << key << std::endl;
    }
    else
    {
        std::cout << "key not found\n";
    }
}

