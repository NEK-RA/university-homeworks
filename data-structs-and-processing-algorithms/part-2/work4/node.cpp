#include "node.h"

Node::Node(char op, Node* left, Node* right){
            this->left = left;
            this->right = right;
            this->data = op;
}

Node::Node(int num){
    this->data = num;
    this->isLeaf = true;
}

Node::~Node(){
    if(this->left != nullptr){
        delete this->left;
    }
    if(this->right != nullptr){
        delete this->right;
    }
}

int Node::getValue(){
    return this->data;
}

float Node::computeValue(){
    if(isLeaf){
        return this->data;
    }
    float result = 0;
    float leftnum = 0;
    float rightnum = 0;
    if(this->left != nullptr){
        leftnum = this->left->computeValue();
    }
    if(this->right != nullptr){
        rightnum = this->right->computeValue();
    }
    switch(this->data){
    case '+':
        result = leftnum + rightnum;
        break;
    case '-':
        result = leftnum - rightnum;
        break;
    case '*':
        result = leftnum * rightnum;
        break;
    case '/':
        result = leftnum / rightnum;
        break;
    }
    return result;
}

void Node::print(int tabs){
    if(this->right != nullptr){
        this->right->print(tabs+1);
    }
    if(tabs >= 1){
        cout << string((tabs-1)*4, ' ');
        cout << "|--<";
    }
    if(this->isLeaf){
        cout << this->data << endl;
    }else{
        cout << string(1, this->data) << endl;
    }
    if(this->left != nullptr){
        this->left->print(tabs+1);
    }
}
