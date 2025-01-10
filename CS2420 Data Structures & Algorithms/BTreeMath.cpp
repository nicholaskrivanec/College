// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif
using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;

// GLOBAL VARIABLES
const int amount = 5;
const char operatorArr[amount] = {'+', '-', '*', '/', '^'};

// Node and Binary Tree Class
template <typename T>
struct Node {
    T info;
    Node<T>* llink{nullptr};
    Node<T>* rlink{nullptr};
};

template <typename T>
class binaryTree {
public:
    binaryTree() {};
    ~binaryTree();
    void addItem(const T& data);
    void preOrder();
    void inOrderTraversal();
    void postOrderTraversal();
    int nodeCount();
    int leavesCount();
    int singleChildCount();
    int levelCount(const unsigned int level);
protected:
    Node<T>* root{nullptr};
    void preOrder(Node<T>* ptr);
    void inOrder(Node<T>* ptr);
    void postOrder(Node<T>* ptr);
    void clear(Node<T>* ptr);
    int nodeCount(Node<T>* ptr);
    int leavesCount(Node<T>* ptr);
    int singleChildCount(Node<T>* ptr);
    int levelCount(const unsigned int level, Node<T>* ptr);
};

// Implementations of binaryTree methods
// Traversals

template <typename T>
void binaryTree<T>::preOrder() {
    preOrder(root);
}

template <typename T>
void binaryTree<T>::preOrder(Node<T>* ptr) {
    if (ptr != nullptr) {
        cout << ptr->info << " ";
        preOrder(ptr->llink);
        preOrder(ptr->rlink);
    }
}

template <typename T>
void binaryTree<T>::inOrderTraversal() {
    inOrder(root);
}

template <typename T>
void binaryTree<T>::inOrder(Node<T>* ptr) {
    if (ptr != nullptr) {
        inOrder(ptr->llink);
        cout << ptr->info << " ";
        inOrder(ptr->rlink);
    }
}

template <typename T>
void binaryTree<T>::postOrderTraversal() {
    postOrder(root);
}

template <typename T>
void binaryTree<T>::postOrder(Node<T>* ptr) {
    if (ptr != nullptr) {
        postOrder(ptr->llink);
        postOrder(ptr->rlink);
        cout << ptr->info << " ";
    }
}

// Node and Tree Counts

template <typename T>
int binaryTree<T>::nodeCount() {
    return nodeCount(root);
}

template <typename T>
int binaryTree<T>::nodeCount(Node<T>* ptr) {
    if (ptr == nullptr) return 0;
    return 1 + nodeCount(ptr->llink) + nodeCount(ptr->rlink);
}

template <typename T>
int binaryTree<T>::leavesCount() {
    return leavesCount(root);
}

template <typename T>
int binaryTree<T>::leavesCount(Node<T>* ptr) {
    if (ptr == nullptr) return 0;
    if (ptr->llink == nullptr && ptr->rlink == nullptr) return 1;
    return leavesCount(ptr->llink) + leavesCount(ptr->rlink);
}

template <typename T>
int binaryTree<T>::singleChildCount() {
    return singleChildCount(root);
}

template <typename T>
int binaryTree<T>::singleChildCount(Node<T>* ptr) {
    if (ptr == nullptr) return 0;
    int count = ((ptr->llink == nullptr) ^ (ptr->rlink == nullptr)) ? 1 : 0;
    return count + singleChildCount(ptr->llink) + singleChildCount(ptr->rlink);
}

template <typename T>
int binaryTree<T>::levelCount(const unsigned int level) {
    return levelCount(level, root);
}

template <typename T>
int binaryTree<T>::levelCount(const unsigned int level, Node<T>* ptr) {
    if (ptr == nullptr || level == 0) return 0;
    if (level == 1) return 1;
    return levelCount(level - 1, ptr->llink) + levelCount(level - 1, ptr->rlink);
}

// Destructor

template <typename T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template <typename T>
void binaryTree<T>::clear(Node<T>* ptr) {
    if (ptr != nullptr) {
        clear(ptr->llink);
        clear(ptr->rlink);
        delete ptr;
    }
}

// Add Item

template <typename T>
void binaryTree<T>::addItem(const T& data) {
    if (root == nullptr) {
        root = new Node<T>{data};
    } else {
        Node<T>* curr = root;
        while (true) {
            if (data < curr->info) {
                if (curr->llink == nullptr) {
                    curr->llink = new Node<T>{data};
                    break;
                }
                curr = curr->llink;
            } else {
                if (curr->rlink == nullptr) {
                    curr->rlink = new Node<T>{data};
                    break;
                }
                curr = curr->rlink;
            }
        }
    }
}

// TreeParser Class
class TreeParser : public binaryTree<string> {
private:
    stack<string> mathStack;
    double castStrToDouble(const string& s);
    string castDoubleToStr(double d);
    void initialize();
    bool isDigit(char c);
    bool isOperator(char c);
    void processExpression(Node<string>* p);
    void computeAnswer(Node<string>* p);

protected:
    string expression;
    int position;

public:
    TreeParser();
    void displayParseTree();
    void processExpression(string& expression);
    string computeAnswer();
};

void TreeParser::computeAnswer(Node<string>* p) {
    if (p != nullptr) {
        computeAnswer(p->llink);
        computeAnswer(p->rlink);

        if (isDigit(p->info[0])) {
            mathStack.push(p->info);
        } else if (isOperator(p->info[0])) {
            if (mathStack.size() < 2) {
                cerr << "Error: Insufficient operands." << endl;
                return;
            }

            double B = castStrToDouble(mathStack.top()); mathStack.pop();
            double A = castStrToDouble(mathStack.top()); mathStack.pop();
            double result = 0.0;

            switch (p->info[0]) {
                case '+': result = A + B; break;
                case '-': result = A - B; break;
                case '*': result = A * B; break;
                case '/':
                    if (B == 0) {
                        cerr << "Error: Division by zero." << endl;
                        return;
                    }
                    result = A / B;
                    break;
                case '^': result = pow(A, B); break;
            }

            mathStack.push(castDoubleToStr(result));
        }
    }
}

string TreeParser::computeAnswer() {
    computeAnswer(root);
    return mathStack.empty() ? "Error" : mathStack.top();
}

void TreeParser::processExpression(string& expression) {
    if (this->expression == expression) return;
    this->expression = expression;
    this->position = 0;
    this->root = new Node<string>;
    processExpression(this->root);
}

void TreeParser::processExpression(Node<string>* p) {
    while (position < expression.length()) {
        char cur = expression[position];

        if (cur == '(') {
            p->llink = new Node<string>;
            ++position;
            processExpression(p->llink);
        } else if (cur == ')') {
            ++position;
            return;
        } else if (isDigit(cur)) {
            string num;
            while (position < expression.length() && (isDigit(expression[position]) || expression[position] == '.')) {
                num += expression[position++];
            }
            p->info = num;
            return;
        } else if (isOperator(cur)) {
            p->info = cur;
            p->rlink = new Node<string>;
            ++position;
            processExpression(p->rlink);
        } else {
            ++position;
        }
    }
}

bool TreeParser::isDigit(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

bool TreeParser::isOperator(char c) {
    for (char op : operatorArr) {
        if (c == op) return true;
    }
    return false;
}

double TreeParser::castStrToDouble(const string& s) {
    return std::stod(s);
}

string TreeParser::castDoubleToStr(double d) {
    return std::to_string(d);
}

void TreeParser::initialize() {
    expression = "";
    position = 0;
    while (!mathStack.empty()) {
        mathStack.pop();
    }
}

TreeParser::TreeParser() {
    initialize();
}

void TreeParser::displayParseTree() {
    cout << "The expression seen using in-order traversal: ";
    inOrderTraversal();
    cout << endl;
    cout << "The expression seen using post-order traversal: ";
    postOrderTraversal();
    cout << endl;
}

void pressAnyKeyToContinue() {
    printf("Press any key to continue\n");
#ifndef __GNUC__
    _getch();
#else
    int c;
    fflush(stdout);
    do c = getchar(); while ((c != '\n') && (c != EOF));
#endif
}

int main() {
    TreeParser* tp = new TreeParser;
    string expression = "(4+7)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(7-4)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(4^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "((2-5)-5)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(5*(6/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "((1 + 2) * (3 + 4))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(543+321)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(((((3+12)-7)*120)/(2+3))^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl;

    pressAnyKeyToContinue();
    delete tp;
    return 0;
}
