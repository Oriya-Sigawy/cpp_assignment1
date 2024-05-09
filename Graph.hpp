// 214984932 Oriyas.07@gmail.com

//TODO-&
/*
this class represents a graph.
*/
#pragma once

#include <vector>
#include <string>
using std::vector;

namespace ariel
{
    class Graph
    {
    private:
        //the graph's fields:
        vector<vector<int>> adjacency_matrix;
        unsigned int vertices;
        unsigned int edges;
        bool directed;
        
        /*
        this method checks if the graph is directed by the adjacency matrix - 
        if the matrix is simetrical, the graph is undirected. 
        otherwise, the graph is directed.
        @returns: true if the graph is directed, false if the graph is undirected.*/
        bool checkDirected();

    public:
        Graph(); // defult constructor

        /*
        this method used to load a matrix to the graph.
        the func initializes the graph's fields.
        */
        void loadGraph(vector<vector<int>> g);

        /*
        this method creates a string in the format:
        "Graph with <num of vertices> vertices and <num of edges> edges."
        @returns: the string that represents the graph.
        */
        std::string to_string();

        //getters:
        unsigned int getNumOfVertices();
        int getAt(unsigned int x, unsigned int y);
        unsigned int getNumOfEdges();
        bool isDirected();
    };
}