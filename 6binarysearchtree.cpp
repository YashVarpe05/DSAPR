#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }
};

class BST
{
private:
    Node *root;

    void deleteTree(Node *node)
    {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    Node *insert(Node *root, int value)
    {
        if (root == nullptr)
        {
            return new Node(value);
        }
        if (value < root->data)
        {
            root->left = insert(root->left, value);
        }
        else if (value > root->data)
        {
            root->right = insert(root->right, value);
        }
        // If value is equal, ignore duplicate
        return root;
    }

    Node *deleteNode(Node *root, int value)
    {
        if (root == nullptr)
        {
            return root;
        }
        if (value < root->data)
        {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->data)
        {
            root->right = deleteNode(root->right, value);
        }
        else
        {
            // Node with only one child or no child
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    bool search(Node *root, int value)
    {
        if (root == nullptr)
        {
            return false;
        }
        if (root->data == value)
        {
            return true;
        }
        if (value < root->data)
        {
            return search(root->left, value);
        }
        return search(root->right, value);
    }

    void inorder(Node *root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    void preorder(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node *root)
    {
        if (root != nullptr)
        {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }

    int height(Node *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + max(height(root->left), height(root->right));
    }

public:
    BST() : root(nullptr) {}

    ~BST()
    {
        deleteTree(root);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    void deleteNode(int value)
    {
        root = deleteNode(root, value);
    }

    bool search(int value)
    {
        return search(root, value);
    }

    bool isEmpty()
    {
        return root == nullptr;
    }

    int getHeight()
    {
        return height(root);
    }

    void display(string traversalType = "inorder")
    {
        if (isEmpty())
        {
            cout << "Tree is empty" << endl;
            return;
        }

        if (traversalType == "inorder")
        {
            cout << "Inorder: ";
            inorder(root);
        }
        else if (traversalType == "preorder")
        {
            cout << "Preorder: ";
            preorder(root);
        }
        else if (traversalType == "postorder")
        {
            cout << "Postorder: ";
            postorder(root);
        }
        cout << endl;
    }
};

int main()
{
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Tree height: " << tree.getHeight() << endl;

    cout << "Tree traversals:" << endl;
    tree.display("inorder");
    tree.display("preorder");
    tree.display("postorder");

    tree.deleteNode(20);
    cout << "\nTree after deleting 20: ";
    tree.display();

    tree.deleteNode(30);
    cout << "Tree after deleting 30: ";
    tree.display();

    tree.deleteNode(50);
    cout << "Tree after deleting 50: ";
    tree.display();

    cout << "Searching for 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}

/*
START

    // Node Structure:
    STRUCT Node:
        INT data
        POINTER left
        POINTER right

    // BST Class:
    CLASS BST:
        PRIVATE:
            POINTER root

        FUNCTION deleteTree(node):
            IF node is NULL:
                RETURN
            DELETE node->left
            DELETE node->right
            DELETE node

        FUNCTION insert(root, value):
            IF root is NULL:
                RETURN new Node(value)
            IF value < root->data:
                root->left = insert(root->left, value)
            ELSE IF value > root->data:
                root->right = insert(root->right, value)
            RETURN root

        FUNCTION deleteNode(root, value):
            IF root is NULL:
                RETURN root
            IF value < root->data:
                root->left = deleteNode(root->left, value)
            ELSE IF value > root->data:
                root->right = deleteNode(root->right, value)
            ELSE:
                IF root has no left child:
                    RETURN root->right
                ELSE IF root has no right child:
                    RETURN root->left
                ELSE:
                    Find minimum value in right subtree
                    Replace root with minimum value node
                    DELETE node from right subtree
            RETURN root

        FUNCTION minValueNode(node):
            WHILE node->left is not NULL:
                node = node->left
            RETURN node

        FUNCTION search(root, value):
            IF root is NULL:
                RETURN false
            IF root->data == value:
                RETURN true
            IF value < root->data:
                RETURN search(root->left, value)
            ELSE:
                RETURN search(root->right, value)

        FUNCTION inorder(root):
            IF root is not NULL:
                inorder(root->left)
                PRINT root->data
                inorder(root->right)

        FUNCTION preorder(root):
            IF root is not NULL:
                PRINT root->data
                preorder(root->left)
                preorder(root->right)

        FUNCTION postorder(root):
            IF root is not NULL:
                postorder(root->left)
                postorder(root->right)
                PRINT root->data

        FUNCTION height(root):
            IF root is NULL:
                RETURN 0
            RETURN 1 + max(height(root->left), height(root->right))

        PUBLIC:
            CONSTRUCTOR BST():
                root = NULL
            DESTRUCTOR ~BST():
                deleteTree(root)

            FUNCTION insert(value):
                root = insert(root, value)

            FUNCTION deleteNode(value):
                root = deleteNode(root, value)

            FUNCTION search(value):
                RETURN search(root, value)

            FUNCTION isEmpty():
                RETURN root == NULL

            FUNCTION getHeight():
                RETURN height(root)

            FUNCTION display(traversalType):
                IF tree is empty:
                    PRINT "Tree is empty"
                ELSE:
                    CALL respective traversal function based on traversalType

    MAIN:
        CREATE BST object "tree"

        INSERT values into tree (50, 30, 20, 40, 70, 60, 80)

        PRINT tree height

        DISPLAY tree traversals (inorder, preorder, postorder)

        DELETE nodes 20, 30, 50 and DISPLAY tree after each deletion

        SEARCH for values 40 and 100 in the tree and print the result

    END

*/