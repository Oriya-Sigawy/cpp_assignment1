/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"

using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;

void printConnected(bool connected)
{
    if (connected)
    {
        cout << "This graph is connected" << endl;
    }
    else
    {
        cout << "This graph is not connected" << endl;
    }
}
void printShortestPath(vector<unsigned int> path)
{
    if (path.size() > 0)
    {
        cout << path[0];
        for (unsigned int x = 1; x < path.size(); x++)
        {
            cout << "->" << path[x];
        }
        cout << endl;
    }
    else
    {
        cout << "-1 (no path)" << endl;
    }
}

void printCycle(vector<unsigned int> cycle)
{
    if (cycle.size() > 0)
    {
        cout << "The cycle is: ";
        for (unsigned int x = 0; x < cycle.size(); x++)
        {
            cout << cycle[x] << "->";
        }
        cout << cycle[0] << endl;
    }
    else
    {
        cout << "There is no cycle in this graph" << endl;
    }
}

void printNegCycle(vector<unsigned int> cycle)
{
    if (cycle.size() > 0)
    {
        cout << "The negative cycle is: ";
        for (unsigned int x = 0; x < cycle.size(); x++)
        {
            cout << cycle[x] << "->";
        }
        cout << cycle[0] << endl;
    }
    else
    {
        cout << "There is no negative cycle in this graph" << endl;
    }
}

void printBipartite(std::array<vector<unsigned int>, 2> bipartite)
{
    if (bipartite[0].size() > 0 && bipartite[1].size() > 0)
    {
        cout << "The Graph is bipartite:" << endl
             << "A = {" << bipartite[0][0];
        for (unsigned int a = 1; a < bipartite[0].size(); a++)
        {
            cout << ", " << bipartite[0][a];
        }
        cout << "}, B = {" << bipartite[1][0];
        for (unsigned int b = 1; b < bipartite[1].size(); b++)
        {
            cout << ", " << bipartite[1][b];
        }
        cout << "}." << endl;
    }
    else
    {
        cout << "This graph is not bipartite" << endl;
    }
}
int main()
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.

    cout << g.to_string() << endl;                        // Should print: "Graph with 3 vertices and 2 edges"
    printConnected(Algorithms::isConnected(g));           // Should print: "the graph is connected".
    printShortestPath(Algorithms::shortestPath(g, 0, 2)); // Should print: 0->1->2
    printCycle(Algorithms::getCycle(g));                  // Should print: "There is no cycle in the graph"
    printBipartite(Algorithms::bipartitePartition(g));    // Should print: "the graph is bipartite A={0, 2}, b={1}"
    printNegCycle(Algorithms::getNegativeCycle(g));       // should print: "There is no negative cycle in this graph"

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    cout << g.to_string() << endl;                        // Should print: "Graph with 5 vertices and 4 edges."     //TODO
    printConnected(Algorithms::isConnected(g));           // Should print: "0" (false).
    printShortestPath(Algorithms::shortestPath(g, 0, 4)); // Should print: "-1" (there is no path between 0 and 4).
    printCycle(Algorithms::getCycle(g));                  // Should print: "The cycle is: 0->1->2->0"
    printBipartite(Algorithms::bipartitePartition(g));    // Should print: "This graph is not bipartite".

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    cout << g.to_string() << endl;                        // Should print: "Graph with 5 vertices and 5 edges." TODO
    printConnected(Algorithms::isConnected(g));           // Should print: "this graph is connected".
    printShortestPath(Algorithms::shortestPath(g, 0, 4)); // Should print: 0->2->3->4. TODO
    printCycle(Algorithms::getCycle(g));                  // Should print: "The cycle is: 0->1->2->0"
    printBipartite(Algorithms::bipartitePartition(g));    // Should print: "This is not s bipartite graph"

    vector<vector<int>> graph5 = {
        {0, 0, 1, 0},
        {-5, 0, 0, 0},
        {0, 2, 0, -3},
        {0, 0, 0, 0}};
    g.loadGraph(graph5);
    printNegCycle(Algorithms::getNegativeCycle(g));      //Shoult print "The negative cycle is 0->1->2"

    // 5x4 matrix that reprsents invalid graph.
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }
}