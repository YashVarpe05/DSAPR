#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

// Stack Node
struct Node {
    char data;
    Node* next;
};

// Stack class to implement stack operations
class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(char value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        char value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    char peek() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if a character is an operand (number or letter)
bool isOperand(char ch) {
    return isalpha(ch) || isdigit(ch);
}

// Infix to Postfix Conversion
string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";
    for (char& ch : infix) {
        if (isOperand(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();  // Pop '(' from the stack
        }
        else {  // Operator
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.isEmpty()) {
        postfix += s.pop();
    }
    return postfix;
}

// Infix to Prefix Conversion
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    Stack s;
    string prefix = "";
    for (char& ch : infix) {
        if (ch == ')') {
            ch = '(';
        }
        else if (ch == '(') {
            ch = ')';
        }
    }
    // Use same logic as infixToPostfix for reversed string
    for (char& ch : infix) {
        if (isOperand(ch)) {
            prefix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                prefix += s.pop();
            }
            s.pop();  // Pop '(' from the stack
        }
        else {  // Operator
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                prefix += s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.isEmpty()) {
        prefix += s.pop();
    }
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

// Evaluate Prefix Expression
int evaluatePrefix(string expr) {
    Stack s;
    for (int i = expr.length() - 1; i >= 0; i--) {
        char ch = expr[i];
        if (isOperand(ch)) {
            s.push(ch - '0');  // Push operand (converted to integer)
        }
        else {
            int operand1 = s.pop();
            int operand2 = s.pop();
            switch (ch) {
                case '+': s.push(operand1 + operand2); break;
                case '-': s.push(operand1 - operand2); break;
                case '*': s.push(operand1 * operand2); break;
                case '/': s.push(operand1 / operand2); break;
                case '^': s.push(pow(operand1, operand2)); break;
            }
        }
    }
    return s.pop();
}

// Evaluate Postfix Expression
int evaluatePostfix(string expr) {
    Stack s;
    for (char ch : expr) {
        if (isOperand(ch)) {
            s.push(ch - '0');  // Push operand (converted to integer)
        }
        else {
            int operand2 = s.pop();
            int operand1 = s.pop();
            switch (ch) {
                case '+': s.push(operand1 + operand2); break;
                case '-': s.push(operand1 - operand2); break;
                case '*': s.push(operand1 * operand2); break;
                case '/': s.push(operand1 / operand2); break;
                case '^': s.push(pow(operand1, operand2)); break;
            }
        }
    }
    return s.pop();
}

int main() {
    string infix = "(A+B)*(C-D)";
    
    cout << "Infix to Postfix: " << infixToPostfix(infix) << endl;
    cout << "Infix to Prefix: " << infixToPrefix(infix) << endl;
    
    string prefix = "*+AB-CD";
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    string postfix = "AB+CD-*";
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;

    return 0;
}
