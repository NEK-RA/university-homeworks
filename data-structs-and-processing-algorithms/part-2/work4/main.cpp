#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include "node.h"
using namespace std;

int getPriority(char c){
    switch(c){
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 2;
    case '(':
    case ')':
        return 1;
    default:
        if(c >= '0' and c <= '9'){
            return 0;
        }
        return -1;
    }
}

vector<string> makePostfix(string e){
    stringstream exp(e);
    stringstream num;
    stack<char> actions;
    vector<string> postfix;
    char c;
    int pos;
    int p;
    char tmpc;
    while(exp >> c){
        p = getPriority(c);
        switch(p){
        case 0:
            num << c;
            while(exp >> c && getPriority(c) == 0){
                num << c;
            }
            postfix.push_back(num.str());
            num.str(string());
            pos = exp.tellg();
            exp.seekg(pos - 1);
            break;
        case 1:
            if(c == '('){
                actions.push(c);
            }else{
                while(actions.top() != '('){
                    postfix.push_back(string(1, actions.top()));
                    actions.pop();
                }
            }
           break;
        case 2:
        case 3:
           while(!actions.empty() && getPriority(actions.top()) >= getPriority(c)){
                postfix.push_back(string(1, actions.top()));
                actions.pop();
           }
           actions.push(c);
           break;
        default:
           break;
        }
    }
    while(!actions.empty()){
        postfix.push_back(string(1, actions.top()));
        actions.pop();
    }
    return postfix;
}

Node* makeTree(vector<string> postfix){
    //1+2+3*4-5/6   -->  1 2 + 3 4 * + 5 6 / -
    stack<Node*> nodes;
    int p;
    char c;

    Node* left;
    Node* right;
    Node* opnode;

    for(int i = 0; i < postfix.size(); i++){
        c = postfix[i][0];
        p = getPriority(c);
        switch(p){
        case 0:
           nodes.push(new Node(stoi(postfix[i])));
            break;
        case 2:
        case 3:
            if(nodes.size() >= 2){
                right = nodes.top();
                nodes.pop();
                left = nodes.top();
                nodes.pop();
                if(left->getValue() != '0' && right->getValue() != '0'){
                    opnode = new Node(postfix[i][0], left, right);
                }else{
                    switch(c){
                    case '+':
                        opnode = new Node(left->getValue() + right->getValue());
                        break;
                    case '-':
                        opnode = new Node(left->getValue() - right->getValue());
                        break;
                    case '*':
                        opnode = new Node(left->getValue() * right->getValue());
                        break;
                    case '/':
                        opnode = nullptr;
                        break;
                    default:
                        continue;
                    }
                }
                nodes.push(opnode);
            }
            break;
        default:
            continue;
        }
    }

    return nodes.top();
}

int main(){
    vector<string> exps{
        "5", "1+2", "1+2+3*4-5/6"
    };
    vector<string> test = makePostfix(exps[2]); // 1 2 + 3 4 * + 5 6 / -
    string expr = "";
    int choice = -1;
    float result = 0;
    Node* root;
    string menu = "\tДерево математического выражения\n"
        "1. Запуск примеров из файла с заданием (5, 1+2, 1+2+3*4-5/6)\n"
        "2. Ввести выражение и построить дерево\n"
        "3. Вычислить значение левого поддерева\n"
        "4. Вычислить значение правого поддерева\n"
        "5. Вычислить значение всего выржаения\n"
        "0. Выход\n"
                  "Выбор: ";
    while(choice != 0){
        cout << menu;
        cin >> choice;
        cin.clear();
        cin.ignore(10000, '\n');
        switch(choice){
        case 1:
            for(int i = 0; i < exps.size(); i++){
                cout << i+1 << ") " << exps[i] << endl;
                root = makeTree(makePostfix(exps[i]));
                root->print();
                cout << "Значение в левом поддереве: ";
                if(root->left != nullptr){
                    cout << root->left->computeValue();
                }else{
                    cout << 0;
                }
                cout << endl;
                cout << "Значение в правом поддереве: ";
                if(root->right != nullptr){
                    cout << root->right->computeValue();
                }else{
                    cout << 0;
                }
                cout << endl;
                cout << "Значение выражения: " << root->computeValue() << endl;
            }
            break;
        case 2:
            cout << "Поддерживаемые операции: +, -, *, /.\nВведите выражение:";
            getline(cin, expr);
            if(expr.size() != 0){
                root = makeTree(makePostfix(expr));
                cout << "Дерево было построено:" << endl;
                root->print();
            }else{
                cout << "Выражение еще не задано!" << endl;
            }
            break;
        case 3:
            if(root != nullptr){
                root = makeTree(makePostfix(expr));
                result = 0;
                if(root->left != nullptr){
                    result = root->left->computeValue();
                    root->left->print();
                    cout << "Значение выражения левого поддерева: " << result << endl;
                }
            }else{
                cout << "Дерево еще не построено!" << endl;
            }
            break;
        case 4:
            if(root  != nullptr){
                root = makeTree(makePostfix(expr));
                result = 0;
                if(root->right != nullptr){
                    result = root->right->computeValue();
                    root->right->print();
                    cout << "Значение выражения правого поддерева: " << result << endl;
                }
            }else{
                cout << "Дерево еще не построено!" << endl;
            }
            break;
        case 5:
            if(root != nullptr){
                root->print();
                result = root->computeValue();
                cout << "Значение выражения всего дерева: " << result << endl;
            }else{
                cout << "Дерево еще не построено!" << endl;
            }
            break;
        case 0:
            break;
        default:
            break;
        }
        cout << "\n\n\n" << endl;
    }
    delete root;
    return 0;
}

