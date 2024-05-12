# System Programming 2 Assignment 1
for this assignment I used 2 classes:  
`Algorithms`: contains static functions (like a library)  
`Graph`: represent a graph and contains the graph's fields and methods  

each one of the classes has a hpp and a cpp files.  

`Algorithms.hpp`: contains the declarations of the public and the private functions.  
`Algorithms.cpp`: contains the implementations for the functions:
- `isConnected`: this function checks the connectivity of a given graph. If it is a directed graph, the function checks a strong connectivity. This function uses the function "traverse", by sending to the function each one of the vertices in the graph. After every call for "traverse", isConnected checks if one of the vertices havn't been visited. If such a vertice exist, the function return false. If the function didn't find such a vertice in all the iterations, the function returns true.    
- `traverse`: the function receives a source node, a graph and an array of booleans. The function marks every vertice as "visited" in the array if the node is reachable from the source.

 - `shortestPath`: this function finds the shortest path from a given start to a given end. The function starts with a call for "getNegativeCycle" to make sure that there is no negative cycle in the graph. Then it checks the shortestPath from the start vertice to the end vertice (which it receives) using dijkstra's algorithm. For that, the function uses a helper function "minDist" that gives her the node with the minimum distance from the source who hasn't part of the shortestPathSet yet. The function returns a vector of all the vertices in the path.
 - `getCycle`: this function detects a cycle in the graph using DFS. It runs DFS on the graph and checks for a back edge. For that, the function uses a helper function "dfs_visit". "dfs_visit" returns two vertices on the cycle, the two ends of the back edge. getCycle find the cycle by marking all the ancestors of the first end, and then traveling of all the second edge's ancestors until it found on that marked as ancestor of the first end. The function returns all the vertices in the cycle.
 -  `dfs_visit`: this function is a recursive function that runs one iteration of DFS on all the neighboors of a given vertice. If the function finds a back edge, it returns an array of the two ends of the back egse. else, it returns an empty array in size 2.
 -  `bipartitePartition`: this function checks if a given graph is bipartite. If this is a graph with no edges, the graph is clearly bipartite, and the function partitions the graph's vertices by their number.
   else, the function uses a helper function "bipartite" to check if the graph is bipartite with every uncolored vertice as the source (for case of a disconnected graph). if bipartite returns false (which means that the graph is not bipartite), bipartitePartition will return an array of two empty vrctors. else, bipartitePartition will partition the vertices for two vectors by their color and returns an array of the two vectors.
  
