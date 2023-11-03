#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node{
public:
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    bool isLeaf = false;

    Node(char op, Node* left, Node* right);
    Node(int num);
    ~Node();

    int getValue();
    float computeValue();
    void print(int tabs = 0);
};

#endif // NODE_H
