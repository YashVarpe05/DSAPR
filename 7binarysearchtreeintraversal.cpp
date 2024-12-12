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
        else
        {
            return search(root->right, value);
        }
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

    void mirror(Node *root)
    {
        if (root != nullptr)
        {
            swap(root->left, root->right);
            mirror(root->left);
            mirror(root->right);
        }
    }

public:
    BST()
    {
        root = nullptr;
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

    void display()
    {
        inorder(root);
        cout << endl;
    }

    void displayMirror()
    {
        mirror(root);
        inorder(root);
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

    cout << "Tree after insertion (Inorder): ";
    tree.display();

    tree.deleteNode(20);
    cout << "Tree after deleting 20 (Inorder): ";
    tree.display();

    tree.deleteNode(30);
    cout << "Tree after deleting 30 (Inorder): ";
    tree.display();

    tree.deleteNode(50);
    cout << "Tree after deleting 50 (Inorder): ";
    tree.display();

    cout << "Searching for 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    cout << "Mirror image of the tree: ";
    tree.displayMirror();

    return 0;
}

/*
Start

1. Define a Node structure with:
   - Integer data
   - Pointers to left and right child nodes

2. Define a BST class with:
   - Private member 'root' to store the root of the tree

3. Define a helper function `insert(root, value)`:
   - If root is null, create a new node with the value
   - If value < root's data, insert in the left subtree
   - If value > root's data, insert in the right subtree
   - Return the root after insertion

4. Define a helper function `deleteNode(root, value)`:
   - If root is null, return root
   - If value < root's data, delete from the left subtree
   - If value > root's data, delete from the right subtree
   - If root's data matches value:
     - If root has no left child, replace root with right child
     - If root has no right child, replace root with left child
     - If root has both children, find the minimum value in the right subtree, replace root's data with that value, and delete the minimum value node

5. Define a helper function `minValueNode(node)`:
   - Traverse the left subtree to find the minimum node

6. Define a helper function `search(root, value)`:
   - If root is null, return false
   - If root's data matches value, return true
   - If value < root's data, search in the left subtree
   - If value > root's data, search in the right subtree

7. Define a helper function `inorder(root)`:
   - Recursively traverse the left subtree, visit the root, and then traverse the right subtree to print the values in order

8. Define a helper function `mirror(root)`:
   - Swap the left and right children of each node, then recursively mirror the left and right subtrees

9. Public methods of BST class:
   - `insert(value)`: Insert value into the tree by calling the recursive insert function
   - `deleteNode(value)`: Delete node with the specified value by calling the recursive delete function
   - `search(value)`: Search for a value in the tree
   - `display()`: Print the tree in inorder traversal
   - `displayMirror()`: Print the mirror image of the tree in inorder traversal

10. In the main function:
    - Insert nodes into the BST
    - Display the tree after each insertion and deletion
    - Search for specific values
    - Display the mirror image of the tree

End


*/