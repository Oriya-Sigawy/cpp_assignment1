// 214984932 Oriyas.07@gmail.com

#pragma once

#include <vector>
#include <string>
using std::vector;

namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjacency_matrix;
        unsigned int vertices;
        unsigned int edges;
        bool directed;
        bool checkDirected();

    public:
        Graph(); // defult empty constructor
        void loadGraph(vector<vector<int>> g);
        std::string to_string();
        unsigned int getNumOfVertices();
        int getAt(unsigned int x, unsigned int y);
        unsigned int getNumOfEdges();
        bool isDirected();
    };
}