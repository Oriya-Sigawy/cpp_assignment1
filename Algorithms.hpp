// 214984932 Oriyas.07@gmail.com

#pragma once

#include <array>
#include <string>
#include <vector>
#include "Graph.hpp"

using std::string;
using std::vector;

namespace ariel
{
    class Algorithms
    {
    public:
        /*
        this func checks whether the graph is connected.
        @param: 
        g: graph to check it's connectivity.
        @returns: true if the graph is connected, otherwise false.
        */
        static bool isConnected(Graph &g);

        /*
        this func gives the shortest path in the graph between the source and the destination using bellman ford's algorithm.
        @param: 
        g: the graph to run the shortest path on.
        source: the verteice to start the shortest path from.
        dest: the destinition of the path.
        @returns: vector that contains the vertices on the shortest path, including the  dource and the destination.*/
        static vector<unsigned int> shortestPath(Graph &g, unsigned int source, unsigned int dest);

        /*
        this func detects a cycle in the graph.
        @param: 
        g: the graph to check the cycles on.
        @returns: vector that contains the vertices on the cycle.
                  if there is no cycle in the graph, the func returns an empty vector.
        */
        static vector<unsigned int> getCycle(Graph &g);

        /*
        this func checks if the graph is bipartite, and divides the vertices into two groups if it is.
        @param:
        g: the graph to check if bipartite.
        @returns: array of two vectors, each vector contains one "side" of the bipartite partition for the vertices.
                  if the graph is NOT bipartite, the func returns array of 2 empty vectors.
                  */
        static std::array<vector<unsigned int>,2> bipartitePartition(Graph &g);

        /*
        this func detects negative cycle on a graph. 
        @param:
        g: the graph to check the negative cycle on.
        @returns: vector that contains the vertices on the negative cycle.
                  if there is no cycle in the graph, the func returns an empty vector.
        */
        static vector<unsigned int> getNegativeCycle(Graph &g);

    private:

        /*
        this func helps to check if a given graph is connected or not.
        the func checks if every vertice in the graph is reachable from a source vertice.
        @params:
        source: the source to statrn every path from
        visited: array of boolean that represents all the vertices that are reachable from the source
        g: the graph to check the paths in
        */
        static void traverse(unsigned int source, bool* visited, Graph& g);

        /*
        this func helps getCycle by running dfs on the graph and searching for back edges 
        @params:
        directed: bool to know if the graph is directed or undirected
        v: the vertice that we check in this operation of the func
        black: array that contains true for the converged vertices
        gray: array that contains true for every vertice that the func didn't finished with yet
        parents: array that for every vertice contains its previos vertice in the shortest path
        g: the graph to do the dfs on
        */
        static std::array<unsigned int, 2> dfs_visit(bool directed, unsigned int v, bool black[], bool *gray, unsigned int parents[], Graph& g); 

        /*
        this func helps bipartitePartition by setting for each vertice a llegal color (by the rules of 2-coloring)
        @params:
        g: the graph to color its vertices
        src: the vertice to start coloring from
        colors: array that holds the color of each vertice
        */  
        static bool bipartite(Graph& g, unsigned int src, int colors[]);
    };
}