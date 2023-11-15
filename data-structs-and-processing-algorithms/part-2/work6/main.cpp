#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

Graph* test1(){
    Graph* g = new Graph();
    g->addNode("One");
    g->addNode("Two");
    g->addNode("Three");
    g->addNode("Four");
    g->addNode("Five");

    g->addBidirectionalPath("One", "Two", 1);
    g->addBidirectionalPath("One", "Three", 2);
    g->addBidirectionalPath("One", "Five", 10);

    g->addBidirectionalPath("Two", "Five", 6);
    g->addBidirectionalPath("Two", "Four", 3);

    g->addBidirectionalPath("Three", "Five", 7);
    g->addBidirectionalPath("Three", "Four", 4);

    g->addBidirectionalPath("Four", "Five", 11);

    return g;
}

Graph* test9(){
    Graph* g = new Graph();
    g->addNode("L");
    g->addNode("B");
    g->addNode("A");
    g->addNode("N");
    g->addNode("G");
    g->addNode("S");
    g->addNode("R");
    g->addNode("D");
    g->addNode("M");

    g->addBidirectionalPath("L", "B", 7);
    g->addBidirectionalPath("L", "B", 10);

    g->addBidirectionalPath("B", "G", 9);
    g->addBidirectionalPath("B", "A", 27);

    g->addBidirectionalPath("A", "M", 15);

    g->addBidirectionalPath("N", "G", 8);
    g->addBidirectionalPath("N", "R", 31);

    g->addBidirectionalPath("G", "S", 11);

    g->addBidirectionalPath("S", "D", 17);
    g->addBidirectionalPath("S", "M", 15);

    g->addBidirectionalPath("D", "R", 32);
    g->addBidirectionalPath("D","M", 21);
    // Shortest L->D: L -> B -> G -> S -> D
    return g;
}

Graph* test8(){
    Graph* g = new Graph();
    g->addNode("One");
    g->addNode("Two");
    g->addNode("Three");
    g->addNode("Four");
    g->addNode("Five");
    g->addNode("Six");
    g->addNode("Seven");

    g->addPath("One", "Two", 4);
    g->addPath("One", "Three", 1);

    g->addPath("Two", "Three", 1);
    g->addPath("Two", "Four", 3);
    g->addPath("Two", "Five", 2);

    g->addPath("Three", "Six", 2);

    g->addPath("Four", "Six", 1);
    g->addPath("Four", "Seven", 3);

    g->addPath("Five", "Seven", 2);

    g->addPath("Six", "Seven", 1);

    // Shortest path 1->6: 1->3->6
    // Shortest path 1->7: 1->3->6->7

    return g;
}

int main(){
    Graph* g = nullptr;
    vector<string> names;
    int choice = -1;
    string name = "";
    string menu = "\tРабота со взешенным неориентированным графом\n"
        "1. Подготовить тестовый граф 1\n"
        "2. Подготовить тестовый граф 9\n"
        "3. (Пере)Создать граф вручную\n"
        "4. Добавить вершину\n"
        "5. Добавить ребро\n"
        "6. Отобразить список вершин\n"
        "7. Определить степень вершины графа\n"
        "8. Найти кратчайший путь между вершинами (метод Дейкстры)\n"
        "9. Тестовый граф №8\n"
        "0. Выход\n"
        "Выбор: ";
    while(choice != 0){
        name = "";
        choice = -1;
        while(!names.empty()){
            names.pop_back();
        }
        cin.clear();
        cout << endl << menu;
        cin >> choice;
        switch(choice){
        case 1:
            if(g != nullptr){
                delete g;
            }
            g = test1();
            break;
        case 2:
            if(g != nullptr){
                delete g;
            }
            g = test9();
            break;
        case 3:
            if(g != nullptr){
                delete g;
            }
            g = new Graph();
            break;
        case 4:
            cout << "Название вершины: ";
            cin >> name;
            g->addNode(name);
            break;
        case 5:
            cout << "Первая вершина ребра: ";
            cin >> name;
            names.push_back(name);
            cout << "Вторая вершина ребра: ";
            cin >> name;
            names.push_back(name);

            choice = -1;
            cout << "Вес ребра: ";
            while(choice < 0){
                cin.clear();
                cin >> choice;
            }
            g->addBidirectionalPath(names[0], names[1], choice);
            break;
        case 6:
            if(g != nullptr){
                g->printNodes();
            }else{
                cout << "Граф еще не создан, отображать нечего" << endl;
            }
            break;
        case 7:
            if(g != nullptr){
                cout << "Укажите название вершины: ";
                cin >> name;
                if(g->exists(name)){
                    cout << "Степень вершины: " << g->nodeDegree(name) << endl;
                }
            }
            break;
        case 8:
            if(g != nullptr){
                cout << "Начальная вершина: ";
                cin >> name;
                names.push_back(name);
                cout << "Конечная вершина: ";
                cin >> name;
                names.push_back(name);
                g->shortPath(names[0], names[1]);
            }else{
                cout << "Граф еще не создан, нет исходных данных для поиска пути" << endl;
            }
            break;
        case 9:
            if(g != nullptr){
                delete g;
            }
            g = test8();
            break;
        default:
            cout << "Выход..." << endl;
            break;
        }
    }
    delete g;
    return 0;
}
