// 214984932 Oriyas.07@gmail.com

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"

using std::vector;

namespace ariel
{
    Graph::Graph()
    {
        // defult
        this->vertices = 5;
        this->adjacency_matrix = vector<vector<int>>(5, vector<int>(5, 0));
        this->edges = 0;
        this->directed = false;
    }

    void Graph::loadGraph(vector<vector<int>> g)
    {
        // reset
        this->vertices = 0;
        this->edges = 0;

        this->vertices = g.size();
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (g[i].size() != vertices)
            {
                throw std::invalid_argument("this is not a square matrix");
            }
        }
        this->adjacency_matrix = vector<vector<int>>(vertices, vector<int>(vertices, 0));
        for (unsigned int i = 0; i < vertices; i++)
        {
            adjacency_matrix[i] = g[i];
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            for (unsigned int j = 0; j < vertices; j++)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    this->edges++;
                }
            }
        }
        this->directed = isDirected();
        if (!directed)
        {
            edges /= 2;
        }
    }

    // getters
    unsigned int Graph::getNumOfVertices()
    {
        return this->vertices;
    }
    int Graph::getAt(unsigned int x, unsigned int y)
    {
        if (x >= this->vertices || y >= this->vertices)
        {
            throw std::out_of_range("");
        }
        return this->adjacency_matrix[x][y];
    }
    unsigned int Graph::getNumOfEdges()
    {
        return this->edges;
    }
    bool Graph::checkDirected()
    {
        return this->directed;
    }
    std::string Graph::to_string()
    {
        std::string str_v = std::to_string(this->vertices);
        std::string str_e = std::to_string(this->edges);
        return "Graph with " + str_v + " vertices and " + str_e + " edges.";
    }

    bool Graph::isDirected()
    {
        bool ans = false;
        for (unsigned int i = 0; i < vertices; i++)
        {
            for (unsigned int j = 0; j < vertices; j++)
            {
                if (adjacency_matrix[i][j] != adjacency_matrix[j][i])
                {
                    ans = true;
                    break;
                }
            }
            if (ans)
            {
                break;
            }
        }
        return ans;
    }
}
