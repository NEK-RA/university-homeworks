#include "graph.h"
#include <limits>
#include <sstream>

Graph::Graph(){
    cout << "Граф создан." << endl;
}

Graph::~Graph(){
    Graph::Node* nd;
    Graph::Path* pt;
    if(this->nodes.size() > 0){
        while(this->nodes.size() > 0){
            nd = this->nodes.front();

            if(nd->paths.size() > 0){
                while(nd->paths.size() > 0){
                    pt = nd->paths.front();
                    delete pt;
                    nd->paths.pop_front();
                }
            }

            delete nd;
            this->nodes.pop_front();
        }
    }
}

Graph::Node* Graph::getNode(string name){
    for(Graph::Node* nd : this->nodes){
        if(nd->name == name){
            return nd;
        }
    }
    return nullptr;
}

bool Graph::exists(string name){
    return (this->getNode(name) != nullptr);
}

bool Graph::addNode(string name){
    if(this->exists(name)){
        cout << "Вершина " << name << " уже присутствует в графе" << endl;
        return false;
    }
    this->nodes.push_back(new Graph::Node({name}));
    return true;
}

bool Graph::addPath(string from, string to, int cost){
    if(this->nodes.size() >= 2){
        Graph::Node* src = nullptr;
        for(Graph::Node* nd : this->nodes){
            if (nd->name == from){
                src = nd;
            }
        }
        if(src != nullptr && this->exists(to)){
            src->paths.push_back(new Graph::Path({to, cost}));
            return true;
        }
    }
    cout << "Одна или обе из указанных вершин не найдены, путь не был добавлен в граф" << endl;
    return false;
}

bool Graph::addBidirectionalPath(string from, string to, int cost){
    bool forward = this->addPath(from, to, cost);
    bool backward = this->addPath(to, from, cost);
    return (forward && backward);
}

int Graph::nodeDegree(string name){
    Graph::Node* nd = this->getNode(name);
    if(nd != nullptr){
        int deg = nd->paths.size();
        for(Graph::Path* pt : nd->paths){
            if(pt->target == nd->name){
                deg++;
            }
        }
        return deg;
    }
    return -1;
}

void Graph::resetTotal(){
    for(Graph::Node* nd : this->nodes){
        nd->total = numeric_limits<float>::infinity();
        nd->previous = nullptr;
    }
}

void Graph::shortPath(string from, string to){
    cout << "Проверка наличия вершины " << from;
    bool from_ex = this->exists(from);
    bool to_ex = this->exists(to);
    if(!from_ex){
        cout << "- вершина НЕ найдена.";
    }
    cout << endl;
    cout << "Проверка наличия вершины " << to;
    if(!to_ex){
        cout << "- вершина НЕ найдена.";
    }
    cout << endl;
    if(!from_ex || !to_ex){
        cout << "Одна из вершин для поиска пути отсутствует в графе, поиск невозможен" << endl;
        return;
    }
    cout << endl;
    // начало алгоритма дейкстры
    queue<Graph::Node*> calc;
    Graph::Node* current = this->getNode(from);
    Graph::Node* next = nullptr;
    current->total = 0;
    calc.push(current);
    float cway = 0;
    // анализ вершин
    while(!calc.empty()){
        current = calc.front();
        // cout << "Анализируется вершина " << current->name << endl;
        for(Graph::Path* pt: current->paths){
            next = this->getNode(pt->target);
            // пропускаем путь от анализируемой вершины до текущей
            if(current->total - pt->distance == next->total){
                continue;
            }
            // анализируем остальные пути
            cway = current->total + pt->distance;
            // если найден более короткий путь до вершины, или она еще не посещена (расстояние infinity)
            if(next->total > cway){
                next->total = cway;
                // анализ вершины завершен, добавляем ее в очередь
                next->previous = current;
                calc.push(next);
                // cout << "Добавили в очередь вершину " << next->name << endl;
            }
        }
        calc.pop();
    }
    // все вершины проанализированы
    // конец алгоритма дейкстры

    current = this->getNode(to);
    cout << "Кратчайший путь составляет " << current->total << " и проходит через следующие вершины:" << endl;
    stack<Graph::Node*> shortest;
    while(current->previous != nullptr){
        shortest.push(current);
        current = current->previous;
    }
    // добавлена вершина, из которой начинается путь
    shortest.push(current);
    // вывод всех вершин
    while(!shortest.empty()){
        cout << shortest.top()->name;
        if(shortest.top()->name != to){
            cout << " -> ";
        }else{
            cout << endl;
        }
        shortest.pop();
    }
    // сброс вычисленных расстояний потому, что в следующий
    // раз стартовая вершина может быть другой и данные будут неактуальны
    this->resetTotal();
}

void Graph::printNodes(){
    int totalPaths = 0;
    for(Graph::Node* nd : this->nodes){
        if(nd != nullptr){
            cout << nd->name << ": ";
            for(Graph::Path* pt : nd->paths){
                cout << pt->target << "[" << pt->distance << "], ";
                totalPaths++;
            }
            cout << endl;
        }       
    }
    cout << "Всего: " << this->nodes.size() << " вершин и " << (totalPaths / 2) << " путей" << endl;
}
