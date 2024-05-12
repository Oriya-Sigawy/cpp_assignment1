// 214984932 Oriyas.07@gmail.com
#include <iostream>
#include <limits.h>
#include <string.h>
#include <bits/stdc++.h>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"
using std::string;
using std::vector;
namespace ariel
{
    // checks strong connectivity for both directed and undirected graphs
    bool Algorithms::isConnected(Graph &g)
    {
        unsigned int vertices = g.getNumOfVertices();
        bool visited[vertices];
        for (unsigned int u = 0; u < vertices; u++)
        {
            for (unsigned int i = 0; i < vertices; i++)
            {
                visited[i] = false;
            }
            traverse(u, visited, g);
            for (unsigned int j = 0; j < vertices; j++)
            {
                if (!visited[j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    void Algorithms::traverse(unsigned int u, bool *visited, Graph &g)
    {
        visited[u] = true;
        for (unsigned int v = 0; v < g.getNumOfVertices(); v++)
        {
            if (g.getAt(u, v))
            {
                if (!visited[v])
                {
                    traverse(v, visited, g);
                }
            }
        }
    }

    vector<unsigned int> Algorithms::shortestPath(Graph &g, unsigned int start, unsigned int end)
    {
        // check that the graph dosen't contain negative cycle
        if (getNegativeCycle(g).size() > 0)
        {
            throw std::invalid_argument("can not find shortestPath in a graph with neg cycle");
        }
        unsigned int vertices = g.getNumOfVertices();
        // check that the source and the destination are real vertices in the graph
        if (start >= vertices || end >= vertices)
        {
            throw std::out_of_range("");
        }
        int dist[vertices];
        unsigned int parents[vertices];
        bool shortestPathSet[vertices];

        for (unsigned int i = 0; i < vertices; i++)
        {
            dist[i] = INT_MAX, shortestPathSet[i] = false, parents[i] = INT_MAX;
        }
        dist[start] = 0;
        for (unsigned int count = 0; count < vertices - 1; count++)
        {
            unsigned int u = minDist(dist, shortestPathSet, vertices);
            shortestPathSet[u] = true;
            for (unsigned int v = 0; v < vertices; v++)
            {
                if (!shortestPathSet[v] && g.getAt(u, v) && dist[u] != INT_MAX && dist[u] + g.getAt(u, v) < dist[v])
                {
                    dist[v] = dist[u] + g.getAt(u, v);
                    parents[v] = u;
                }
            }
        }
        if (dist[end] == INT_MAX)
        {
            return vector<unsigned int>();
        }
        vector<unsigned int> ans;
        unsigned int i = end;
        while (i != start)
        {
            ans.push_back(i);
            i = parents[i];
        }
        ans.push_back(start);
        std::reverse(ans.begin(), ans.end());

        return ans;
    }

    unsigned int Algorithms::minDist(int *dist, bool *shortestPathSet, unsigned int vertices)
    {
        int min = INT_MAX;
        unsigned int min_index;

        for (unsigned int v = 0; v < vertices; v++)
        {
            if (shortestPathSet[v] == false && dist[v] <= min)
            {
                min = dist[v], min_index = v;
            }
        }
        return min_index;
    }

    vector<unsigned int> Algorithms::getCycle(Graph &g)
    {
        bool directed = g.isDirected();
        unsigned int vertices = g.getNumOfVertices();
        vector<unsigned int> result;
        bool black[vertices];
        bool gray[vertices];
        unsigned int parents[vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            black[i] = false;
            gray[i] = false;
            parents[i] = INT_MAX;
        }

        for (unsigned int i = 0; i < vertices; i++)
        {
            if (!black[i])
            {
                std::array<unsigned int, 2> ans = dfs_visit(directed, i, black, gray, parents, g);
                if (ans[0] != INT_MAX && ans[1] != INT_MAX)
                {
                    unsigned int p = ans[0];
                    while (p != ans[1])
                    {
                        result.push_back(p);
                        p = parents[p];
                    }
                    result.push_back(ans[1]);
                    std::reverse(result.begin(), result.end());
                    return result;
                }
            }
        }
        return result;
    }

    std::array<unsigned int, 2> Algorithms::dfs_visit(bool directed, unsigned int v, bool black[], bool *gray, unsigned int parents[], Graph &g)
    {
        std::array<unsigned int, 2> ans = {INT_MAX, INT_MAX};
        gray[v] = true;
        for (unsigned int i = 0; i < g.getNumOfVertices(); ++i)
        {
            if (g.getAt(v, i) != 0)
            {
                if (gray[i] && (directed || !(i == parents[v])))
                {
                    ans[0] = v;
                    ans[1] = i;
                    return ans;
                }
                else if (!black[i] && !gray[i])
                {
                    parents[i] = v;
                    ans = dfs_visit(directed, i, black, gray, parents, g);
                    if (ans[0] != INT_MAX && ans[1] != INT_MAX)
                    {
                        return ans;
                    }
                }
            }
        }

        gray[v] = false;
        black[v] = true;
        return ans;
    }

    std::array<vector<unsigned int>, 2> Algorithms::bipartitePartition(Graph &g)
    {
        std::array<vector<unsigned int>, 2> ans;
        unsigned int vertices = g.getNumOfVertices();
        if (g.getNumOfEdges() == 0)
        {
            for (unsigned int i = 0; i < vertices; i++)
            {
                if (i % 2 == 0)
                {
                    ans[0].push_back(i);
                }
                else
                {
                    ans[1].push_back(i);
                }
            }
            return ans;
        }
        int colors[vertices];
        for (unsigned int i = 0; i < vertices; ++i)
        {
            colors[i] = -1;
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (colors[i] == -1)
            {
                if (!bipartite(g, i, colors))
                {
                    return ans;
                }
            }
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (colors[i] == 1)
            {
                ans[0].push_back(i);
            }
            else
            {
                ans[1].push_back(i);
            }
        }
        return ans;
    }
    bool Algorithms::bipartite(Graph &g, unsigned int src, int colors[])
    {
        colors[src] = 1;
        // BFS travel
        std::queue<unsigned int> q;
        q.push(src);
        while (!q.empty())
        {
            unsigned int u = q.front();
            q.pop();

            for (unsigned int v = 0; v < g.getNumOfVertices(); ++v)
            {
                if (g.getAt(u, v) && colors[v] == -1)
                {
                    colors[v] = 1 - colors[u];
                    q.push(v);
                }
                else if (g.getAt(u, v) && colors[v] == colors[u])
                    return false;
            }
        }
        return true;
    }

    vector<unsigned int> Algorithms::getNegativeCycle(Graph &g)
    {
        unsigned int vertices = g.getNumOfVertices();
        unsigned int parents[vertices];
        bool connectedToCycle[vertices];
        int dist[vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            parents[i] = INT_MAX;
            dist[i] = INT_MAX;
            connectedToCycle[i] = false;
        }
        for (unsigned int source = 0; source < vertices; source++)
        {
            if (dist[source] != INT_MAX)
            {
                continue;
            }
            dist[source] = 0;
            for (unsigned int k = 0; k < vertices; k++)
            {
                for (unsigned int i = 0; i < vertices; i++)
                {
                    for (unsigned int j = 0; j < vertices; j++)
                    {
                        if (g.getAt(i, j) != 0 && dist[i] != INT_MAX && dist[j] > dist[i] + g.getAt(i, j) && !(parents[i] == j))
                        {
                            dist[j] = dist[i] + g.getAt(i, j);
                            parents[j] = i;
                        }
                    }
                }
            }
            unsigned int cycleStart = INT_MAX;
            for (unsigned int i = 0; i < vertices; i++)
            {
                for (unsigned int j = 0; j < vertices; j++)
                {
                    if (g.getAt(i, j) != 0 && dist[i] != INT_MAX && dist[j] > dist[i] + g.getAt(i, j) && !(parents[i] == j))
                    {
                        while (!connectedToCycle[j])
                        {
                            connectedToCycle[j] = true;
                            j = parents[j];
                        }
                        cycleStart = j;
                        break;
                    }
                }
                if (cycleStart != INT_MAX)
                {
                    break;
                }
            }
            if (cycleStart != INT_MAX)
            {
                vector<unsigned int> ans;
                ans.push_back(cycleStart);
                unsigned int traverseCycle = parents[cycleStart];
                while (traverseCycle != cycleStart)
                {
                    ans.push_back(traverseCycle);
                    traverseCycle = parents[traverseCycle];
                }
                std::reverse(ans.begin(), ans.end());
                return ans;
            }
        }
        return vector<unsigned int>();
    }
}