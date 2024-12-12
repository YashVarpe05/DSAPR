#include <iostream>
using namespace std;

// Node of the threaded binary tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    bool leftThread;  // If true, left is a thread, not a real left child
    bool rightThread; // If true, right is a thread, not a real right child
};

// Class for Threaded Binary Tree
class ThreadedBinaryTree
{
private:
    Node *root;

    // Helper function to insert node
    void insertHelper(Node *&root, int value)
    {
        if (!root)
        {
            root = new Node();
            root->data = value;
            root->left = root->right = nullptr;
            root->leftThread = root->rightThread = false;
            return;
        }

        if (value < root->data)
        {
            if (root->leftThread)
            {
                Node *temp = root->left;
                root->left = new Node();
                root->left->data = value;
                root->left->left = temp;
                root->left->right = root;
                root->leftThread = false;
                root->left->leftThread = true;
                root->left->rightThread = true;
            }
            else
            {
                insertHelper(root->left, value);
            }
        }
        else if (value > root->data)
        {
            if (root->rightThread)
            {
                Node *temp = root->right;
                root->right = new Node();
                root->right->data = value;
                root->right->right = temp;
                root->right->left = root;
                root->rightThread = false;
                root->right->leftThread = true;
                root->right->rightThread = true;
            }
            else
            {
                insertHelper(root->right, value);
            }
        }
    }

    // Helper function to search a value
    Node *searchHelper(Node *root, int value)
    {
        while (root != nullptr)
        {
            if (value == root->data)
            {
                return root;
            }
            else if (value < root->data)
            {
                if (root->leftThread)
                {
                    break;
                }
                root = root->left;
            }
            else
            {
                if (root->rightThread)
                {
                    break;
                }
                root = root->right;
            }
        }
        return nullptr;
    }

    // Helper function to clear the tree (recursive)
    void clearHelper(Node *root)
    {
        if (root != nullptr)
        {
            if (!root->leftThread)
            {
                clearHelper(root->left);
            }
            if (!root->rightThread)
            {
                clearHelper(root->right);
            }
            delete root;
        }
    }

    // Helper function for in-order traversal
    void inorderHelper(Node *root)
    {
        while (root != nullptr)
        {
            if (!root->leftThread)
            {
                root = root->left;
            }
            else
            {
                cout << root->data << " ";
                if (root->rightThread)
                {
                    root = root->right;
                }
                else
                {
                    root = root->right;
                }
            }
        }
    }

public:
    ThreadedBinaryTree()
    {
        root = nullptr;
    }

    // Insert a node in the tree
    void insert(int value)
    {
        insertHelper(root, value);
    }

    // Search for a node in the tree
    Node *search(int value)
    {
        return searchHelper(root, value);
    }

    // Clear the tree
    void clear()
    {
        clearHelper(root);
        root = nullptr;
    }

    // In-order traversal of the tree
    void inorder()
    {
        inorderHelper(root);
        cout << endl;
    }
};

// Driver program
int main()
{
    ThreadedBinaryTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);

    cout << "In-order Traversal: ";
    tree.inorder(); // Should print: 5 10 15 20 30

    int searchValue = 15;
    Node *foundNode = tree.search(searchValue);
    if (foundNode)
    {
        cout << "Node " << searchValue << " found!" << endl;
    }
    else
    {
        cout << "Node " << searchValue << " not found!" << endl;
    }

    tree.clear();
    cout << "Tree cleared!" << endl;

    tree.inorder(); // Should not print anything, since the tree is empty

    return 0;
}

/*
STRUCT Node:
    INTEGER data
    POINTER left
    POINTER right
    BOOLEAN leftThread
    BOOLEAN rightThread

CLASS ThreadedBinaryTree:
    PRIVATE:
        POINTER root

    FUNCTION insertHelper(POINTER root, INTEGER value):
        IF root is NULL:
            CREATE new node with value
            RETURN

        IF value < root->data:
            IF leftThread is TRUE:
                INSERT node to left with thread handling
            ELSE:
                RECURSIVELY call insertHelper(root->left, value)

        ELSE IF value > root->data:
            IF rightThread is TRUE:
                INSERT node to right with thread handling
            ELSE:
                RECURSIVELY call insertHelper(root->right, value)

    FUNCTION searchHelper(POINTER root, INTEGER value):
        WHILE root is not NULL:
            IF value == root->data:
                RETURN root
            ELSE IF value < root->data:
                IF leftThread is TRUE:
                    BREAK loop
                root = root->left
            ELSE:
                IF rightThread is TRUE:
                    BREAK loop
                root = root->right
        RETURN NULL

    FUNCTION clearHelper(POINTER root):
        IF root is not NULL:
            IF leftThread is FALSE:
                RECURSIVELY call clearHelper(root->left)
            IF rightThread is FALSE:
                RECURSIVELY call clearHelper(root->right)
            DELETE root

    FUNCTION inorderHelper(POINTER root):
        WHILE root is not NULL:
            IF leftThread is FALSE:
                MOVE to left child
            ELSE:
                PRINT root->data
                IF rightThread is TRUE:
                    MOVE to right thread
                ELSE:
                    MOVE to right child

    PUBLIC:
        CONSTRUCTOR:
            root = NULL

        FUNCTION insert(INTEGER value):
            CALL insertHelper(root, value)

        FUNCTION search(INTEGER value):
            RETURN CALL searchHelper(root, value)

        FUNCTION clear():
            CALL clearHelper(root)
            root = NULL

        FUNCTION inorder():
            CALL inorderHelper(root)
            PRINT newline

MAIN:
    CREATE tree of ThreadedBinaryTree
    INSERT nodes: 10, 20, 30, 5, 15
    PRINT "In-order Traversal"
    CALL inorder
    SEARCH for value 15
    IF found, PRINT "Node found"
    ELSE PRINT "Node not found"
    CLEAR the tree
    PRINT "Tree cleared"
    CALL inorder (should not print anything)


*/
