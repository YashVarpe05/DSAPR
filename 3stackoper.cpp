#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(char x) {
        Node* temp = new Node;
        temp->data = x;
        temp->next = top;
        top = temp;
    }

    char pop() {
        if (isEmpty()) return '\0';
        char x = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return x;
    }

    char peek() {
        return (isEmpty()) ? '\0' : top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        } else if (isOperator(c)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) {
                postfix += s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (char& c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> s;

    for (char c : postfix) {
        if (isdigit(c)) {
            s.push(c - '0');
        } else if (isOperator(c)) {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (c) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.top();
}

int evaluatePrefix(string prefix) {
    stack<int> s;
    reverse(prefix.begin(), prefix.end());

    for (char c : prefix) {
        if (isdigit(c)) {
            s.push(c - '0');
        } else if (isOperator(c)) {
            int a = s.top(); s.pop();
            int b = s.top(); s.pop();
            switch (c) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.top();
}

int main() {
    string infix = "(3+5)*2";

    cout << "Infix: " << infix << endl;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    string prefix = infixToPrefix(infix);
    cout << "Prefix: " << prefix << endl;

    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}

/*
DATA STRUCTURES:
   Node:
      - data (character)
      - next (pointer to Node)

   Stack:
      - top (pointer to Node)

OPERATIONS:

1. INITIALIZE_STACK
   Set top = null

2. PUSH(character x)
   Create new Node temp
   Set temp.data = x
   Set temp.next = top
   Set top = temp

3. POP
   IF stack is empty THEN
      Return null character
   Set x = top.data
   Set temp = top
   Move top to next node
   Delete temp
   Return x

4. PEEK
   IF stack is empty THEN
      Return null character
   ELSE
      Return top.data

5. IS_EMPTY
   Return (top is null)

*/