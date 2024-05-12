// 214984932 Oriyas.07@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

/*
this func checks if the vertices in the vector that Algorithms::getCycle returned indeed creates a cycle in g.
@params:
g: the graph to check the cycle on
c: the vector of vertices that getCycle returns
@returns: true if the vertices creates a cycle, false otherwise
*/
bool testCycle(ariel::Graph g, vector<unsigned int> c)
{
    for (unsigned int i = 0; i < c.size() - 1; i++)
    {
        if (!g.getAt(c[i], c[i + 1]))
        {
            return false;
        }
    }
    if (!g.getAt(c[c.size() - 1], c[0]))
    {
        return false;
    }
    return true;
}

/*
this func checks if the vertices in the vector that Algorithms::getNegativeCycle returned indeed creates a negative cycle in g.
@params:
g: the graph to check the cycle on
c: the vector of vertices that getNegativeCycle returns
@returns: true if the vertices creates a negative cycle, false otherwise
*/
bool testNegCycle(ariel::Graph g, vector<unsigned int> c)
{
    int sum = 0;
    for (unsigned int i = 0; i < c.size() - 1; i++)
    {
        if (!g.getAt(c[i], c[i + 1]))
        {
            return false;
        }
        sum += g.getAt(c[i], c[i + 1]);
    }
    if (!g.getAt(c[c.size() - 1], c[0]))
    {
        return false;
    }
    sum += g.getAt(c[c.size() - 1], c[0]);
    if (sum >= 0)
    {
        return false;
    }
    return true;
}
/*
this func checks if the 2 vectors of the array that Algorithms::bipartite returned are indeed foreign,
and that every edge in the graph goes from a vertice in one vector to a vertice in the other vector.
@params:
g: the graph to check if bipartite
result: array of 2 vectors which holds the two groups divation for the graph's vertices.
@returns: true if the two vectors are a legal partition of the graph vertices, otherwise false.
*/
bool testBipartite(ariel::Graph g, std::array<vector<unsigned int>, 2> result)
{
    for (unsigned int i = 0; i < result[0].size(); i++)
    {
        for (unsigned int j = 0; j < result[0].size(); j++)
        {
            if (g.getAt(result[0][i], result[0][j]) != 0)
            {
                return false;
            }
        }
    }
    for (unsigned int i = 0; i < result[1].size(); i++)
    {
        for (unsigned int j = 0; j < result[1].size(); j++)
        {
            if (g.getAt(result[1][i], result[1][j]) != 0)
            {
                return false;
            }
        }
    }
    return true;
}

////tests for Graph.cpp
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test to_string in undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.to_string() == "Graph with 5 vertices and 6 edges.");
}
TEST_CASE("Test to_string in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {3, 0, 0, 0, 4},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(g.to_string() == "Graph with 5 vertices and 6 edges.");
}

TEST_CASE("Test to_string on graph with 1 vertice")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0}};
    g.loadGraph(graph2);
    CHECK(g.to_string() == "Graph with 1 vertices and 0 edges.");
}
TEST_CASE("Test getNumOfVertices")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumOfVertices() == 5);
}
TEST_CASE("Test getNumOfVertices in a graph with 1 vertice")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0}};
    g.loadGraph(graph2);
    CHECK(g.getNumOfVertices() == 1);
}

TEST_CASE("Test getAt with indexes out of bounds")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(g.getAt(3, 0));
}

TEST_CASE("Test getAt in index out of bounds")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(g.getAt(6, 7));
}

TEST_CASE("Test getAt")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getAt(2, 0) == 1);
}

TEST_CASE("Test getNumOfEdges in a Graph with no edges")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = {
        {0, 0},
        {0, 0}};
    g.loadGraph(graph1);
    CHECK(g.getNumOfEdges() == 0);
}

TEST_CASE("Test getNumOfEdges in a clique")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph2);
    CHECK(g.getNumOfEdges() == 3);
}

TEST_CASE("Test getNumOfEdges in a undirected Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(g.getNumOfEdges() == 6);
}

TEST_CASE("Test getNumOfEdges in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {3, 0, 0, 0, 4},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(g.getNumOfEdges() == 6);
}

TEST_CASE("Test isDirected in a undirected Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(g.isDirected() == false);
}

TEST_CASE("Test isDirected in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {3, 0, 0, 0, 4},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(g.isDirected() == true);
}

TEST_CASE("Test isDirected in a graph with no edges")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0}};
    g.loadGraph(graph2);
    CHECK(g.isDirected() == false);
}

/////////test Algorithms.cpp
TEST_CASE("Test isConnected in a clique")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test isConnected in a connected undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test isConnected in undirected disconnected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test isConnected in directed weakly connected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {1, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test isConnected in directed strongly connected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 1, 1},
        {2, 0, 0, 0, 0},
        {0, 0, 3, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test isConnected in directed disconnected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath with index out of bounds")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(ariel::Algorithms::shortestPath(g, 3, 0));
}

TEST_CASE("Test shortestPath in directed graph whith negative edges (dijkstra fails here)")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2, 2, 0},
        {0, 0, 0, 1},
        {0, -2, 0, 0},
        {0, 0, 0, 0}};
    vector<unsigned int> check = {0, 2, 1, 3};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == check);
}

TEST_CASE("Test shortestPath in directed graph with negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1, 0},
        {-5, 0, 0, 0},
        {0, 2, 0, -3},
        {0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 2));
}

TEST_CASE("Test shortestPath in undirected connected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> check = {0, 1, 2};
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == check);
}

TEST_CASE("Test shortestPath in undirected disconnected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4).size() == 0);
}

TEST_CASE("Test shortestPath in undirected graph with negative edge")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 10, -1, 1, 0},
        {10, 0, 10, 0, 0},
        {-1, 10, 0, 0, 2},
        {1, 0, 0, 0, 0},
        {0, 0, 2, 0, 0}};
    g.loadGraph(graph);
    vector<unsigned int> check = {1, 2, 0};
    CHECK(ariel::Algorithms::shortestPath(g, 1, 0) == check);
}
TEST_CASE("Test shortestPath in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {1, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    vector<unsigned int> check = {1, 2};
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == check);
}

TEST_CASE("Test shortestPath in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {1, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2).size() == 0);
}

TEST_CASE("Test getCycle in undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> check = ariel::Algorithms::getCycle(g);
    CHECK(testCycle(g, check));
}

TEST_CASE("Test getCycle in undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getCycle(g).size() == 0);
}

TEST_CASE("Test getCycle in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {1, 0, 0},
        {0, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getCycle(g);
    CHECK(testCycle(g, ans));
}

TEST_CASE("Test getCycle in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getCycle(g).size() == 0);
}

TEST_CASE("Test getCycle in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getCycle(g);
    CHECK(testCycle(g, ans));
}

TEST_CASE("Test bipartitePartition in undirected Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in undirected Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    bool check = result[0].size() == 0 && result[1].size() == 0;
    CHECK(check == true);
}
TEST_CASE("Test bipartitePartition in directed Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0}};
    g.loadGraph(graph3);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in directed Graph")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph3);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    bool check = result[0].size() == 0 && result[1].size() == 0;
    CHECK(check == true);
}

TEST_CASE("Test bipartitePartition in directed Graph with cycle with even length")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in directed Graph with cycle with even length and a tail")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in graph with no edges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0},
        {0, 0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in Graph with 1 vertex")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    CHECK(testBipartite(g, result));
}

TEST_CASE("Test bipartitePartition in Graph with cycle with odd length")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 1, 0, 0, 1, 0}};
    g.loadGraph(graph);
    std::array<vector<unsigned int>, 2> result = ariel::Algorithms::bipartitePartition(g);
    bool check = result[0].size() == 0 && result[1].size() == 0;
    CHECK(check == true);
}

TEST_CASE("Test getNegativeCycle in undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, -5},
        {1, 0, 2},
        {-5, 2, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getNegativeCycle(g);
    CHECK(testNegCycle(g, ans));
}

TEST_CASE("Test getNegativeCycle in undirected graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, -1},
        {-1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getNegativeCycle(g).size() == 0);
}

TEST_CASE("Test getNegativeCycle in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1, 0},
        {-5, 0, 0, 0},
        {0, 2, 0, -3},
        {0, 0, 0, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getNegativeCycle(g);
    CHECK(testNegCycle(g, ans));
}

TEST_CASE("Test getNegativeCycle in directed graph")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {0, 0, -5},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getNegativeCycle(g).size() == 0);
}

TEST_CASE("Test getNegativeCycle in directed graph with cycle with weight 0")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 0, -1},
        {-2, 0, 0},
        {0, 3, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getNegativeCycle(g).size() == 0);
}

TEST_CASE("Test getNegativeCycle in directed graph with inner cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 1},
        {1, 0, 3, -8, 0},
        {0, 3, 0, 3, 0},
        {0, -8, 3, 0, 1},
        {1, 0, 0, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getNegativeCycle(g);
    CHECK(testNegCycle(g, ans));
}

TEST_CASE("Test getNegativeCycle in directed graph with no cycle but edges with negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 0, -1},
        {-1, 0, -1},
        {0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::getNegativeCycle(g).size() == 0);
}

TEST_CASE("Test getNegativeCycle in directed graph with negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0},
        {1, 0, 0, -5},
        {0, 1, 0, 0},
        {0, 0, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getNegativeCycle(g);
    CHECK(testNegCycle(g, ans));
}

TEST_CASE("Test getNegativeCycle in undirected disconnected graph with negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, -2, 0, 0, 0},
        {0, -2, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, -5},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, -5, 1, 0}};
    g.loadGraph(graph);
    vector<unsigned int> ans = ariel::Algorithms::getNegativeCycle(g);
    CHECK(testNegCycle(g, ans));
}

