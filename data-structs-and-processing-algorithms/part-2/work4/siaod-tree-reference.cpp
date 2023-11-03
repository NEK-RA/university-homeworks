#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

class Node { // Добавил отдельный класс для работы со списком
public:
    char data;
    Node* left;
    Node* right;

    Node(char data) {
        this->data = data;
        this->left = this->right = nullptr;
    };

    Node(char data, Node* left, Node* right) {
        this->data = data;
        this->left = left;
        this->right = right;
    };
    friend class Tree;
};

class Tree { // Отдельный класс для работы с деревом
public: // Разделил внешние функции которые вызываются извне
    struct Trunk {
        Trunk* prev;
        string str;
        Trunk(Trunk* prev, string str) {
            this->prev = prev;
            this->str = str;
        }
    };
    Tree() = default;
    string convert(string infix) {
        int i = 0;
        string postfix = "";
        stack <int>s;

        while (infix[i] != '\0')
        {
            if ((int)infix[i] >= '0' && (int)infix[i] <= '9') {
                postfix += infix[i];
                i++;
            }
            else if (infix[i] == '(') {
                s.push(infix[i]);
                i++;
            }
            else if (infix[i] == ')') {
                while (s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
                i++;
            }
            else {
                while (!s.empty() && priority(infix[i]) <= priority(s.top())) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
                i++;
            }
        }
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }
        cout << "Postfix is : " << postfix;
        return postfix;
    }
    Node* construct(string postfix) {
        if (postfix.length() == 0) {
            return nullptr;
        }
        stack<Node*> s;
        for (char c : postfix) {
            if (isOperator(c)) {
                Node* x = s.top();
                s.pop();

                Node* y = s.top();
                s.pop();

                Node* node = new Node(c, y, x);

                s.push(node);
            }
            else {
                s.push(new Node(c));
            }
        }
        return s.top();
    }
    void prefixPrint(Node* root, string& prefix) {
        if (root == NULL)
            return;
        prefix += root->data;
        prefixPrint(root->left, prefix);
        prefixPrint(root->right, prefix);
    }
    float evaluateExpressionTree(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        if (isdigit(root->data)) {
            return root->data - '0';
        }

        float leftValue = evaluateExpressionTree(root->left);
        float rightValue = evaluateExpressionTree(root->right);

        switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        default:
            return 0;
        }
    }
    double evaluatePrefix(string exprsn) {
        stack<double> Stack;
        for (int j = exprsn.size() - 1; j >= 0; j--) {
            if (!isOperator(exprsn[j]))
                Stack.push(exprsn[j] - '0');
            else {
                double o1 = Stack.top();
                Stack.pop();
                double o2 = Stack.top();
                Stack.pop();
                switch (exprsn[j]) {
                case '+':
                    Stack.push(o1 + o2);
                    break;
                case '-':
                    Stack.push(o1 - o2);
                    break;
                case '*':
                    Stack.push(o1 * o2);
                    break;
                case '/':
                    Stack.push(o1 / o2);
                    break;
                }
            }
        }
        return Stack.top();
    }
    void printTree(Node* root, Trunk* prev, bool isLeft) {
        if (root == nullptr)
            return;
        string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);
        printTree(root->right, trunk, true);

        if (!prev)
            trunk->str = "———";
        else if (isLeft) {
            trunk->str = ".———";
            prev_str = "   |";
        }
        else {
            trunk->str = "`———";
            prev->str = prev_str;
        }
        showTrunks(trunk);
        cout << " " << root->data << endl;
        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, false);
    }
private: // Разделил все внутренние функции которые работают только во внешних
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }
    void showTrunks(Trunk* p) {
        if (p == nullptr) {
            return;
        }
        showTrunks(p->prev);
        cout << p->str;
    }
    int priority(char alpha) {
        if (alpha == '+' || alpha == '-')
            return 1;

        if (alpha == '*' || alpha == '/')
            return 2;

        if (alpha == '^')
            return 3;
        return 0;
    }
};


int main()
{
    setlocale(LC_ALL, "RUS");

    string infix;
    string Prefix = "";
    string Postfix = "";
    cout << "Введите исходное выражение" << endl;
    cin >> infix;

    Tree myTree;
    Postfix = myTree.convert(infix); // Определил что вычисление постфикса
    Node* root = myTree.construct(Postfix); //Создал дерево в структуре списка
    cout << endl << endl << endl;
    myTree.printTree(root, NULL, false); // Печатает дерево
    myTree.prefixPrint(root, Prefix); // Выводит префикс по дереву
    cout << "Префиксное выражение: " << Prefix;
    cout << endl;
    cout << "Значение выражения по дереву: " << myTree.evaluateExpressionTree(root) << endl; //Твоя функция которая вычисляет значение по дереву
    cout << "Значение выражения по префиксу: " << myTree.evaluatePrefix(Prefix) << endl; // Моя функция которая вычисляет значение по префиксу
    return 0;
}
