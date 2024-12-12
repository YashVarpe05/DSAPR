#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;
    
    Node* insert(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }
        if (value < root->data) {
            root->left = insert(root->left, value);
        } else if (value > root->data) {
            root->right = insert(root->right, value);
        }
        return root;
    }
    
    Node* deleteNode(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }
        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        } else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }
    
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    
    bool search(Node* root, int value) {
        if (root == nullptr) {
            return false;
        }
        if (root->data == value) {
            return true;
        }
        if (value < root->data) {
            return search(root->left, value);
        } else {
            return search(root->right, value);
        }
    }
    
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }
    
public:
    BST() {
        root = nullptr;
    }
    
    void insert(int value) {
        root = insert(root, value);
    }
    
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }
    
    bool search(int value) {
        return search(root, value);
    }
    
    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);
    
    cout << "Tree after insertion: ";
    tree.display();
    
    tree.deleteNode(20);
    cout << "Tree after deleting 20: ";
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
