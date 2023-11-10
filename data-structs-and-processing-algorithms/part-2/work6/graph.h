#include <iostream>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Graph{

    public:
        struct Path{
            string target;
            int distance;
        };
        struct Node{
            string name;
            list<Path*> paths;
            float total = numeric_limits<float>::infinity();
            Node* previous = nullptr;
        };

        Graph();
        ~Graph();
        Node* getNode(string name);
        bool exists(string name);
        bool addNode(string name);
        bool addPath(string from, string to, int cost);
        bool addBidirectionalPath(string from, string to, int cost);
        int nodeDegree(string name);
        void resetTotal();
        void shortPath(string from, string to);
        void printNodes();
    
    private:
        list<Node*> nodes;
};
