//214984932 Oriyas.07@gmail.com
# Systems Programming 2 Assignment 1
For this assignment I used 2 classes:  
`Algorithms`: contains static functions (like a library)  
`Graph`: represents a graph and contains the graph's fields and methods  

each one of the classes has a hpp and a cpp files.  

`Algorithms.hpp`: contains the declarations of the public and the private functions.  
`Algorithms.cpp`: contains the implementations for the functions:
- `isConnected`: this function checks the connectivity of a given graph. If it is a directed graph, the function checks a strong connectivity. This function uses the function "traverse", by sending it each one of the vertices in the graph. After every call for "traverse", isConnected checks if there is a vertice that hasn't been visited. If such a vertice exist, the function return false. If the function didn't find such a vertice in all the iterations, the function returns true.    
- `traverse`: the function receives a source vertice, a graph and an array of booleans. The function marks every vertice as "visited" in the array if it is reachable from the source.

 - `shortestPath`: this function finds the shortest path from a given start to a given end. The function starts with a call for "getNegativeCycle" to make sure that there is no negative cycle in the graph. Then it checks the shortestPath from the start vertice to the end vertice (which it receives) using dijkstra's algorithm. For that, the function uses a helper function "minDist" that gives her the vertice with the minimum distance from the source who hasn't part of the shortestPathSet yet. The function returns a vector of all the vertices in the path.
 - `getCycle`: this function detects a cycle in the graph using DFS. It runs DFS on the graph and checks for a back edge. For that, the function uses a helper function "dfs_visit". "dfs_visit" returns two vertices on the cycle, the two ends of the back edge. getCycle find the cycle by marking all the ancestors of the first end, and then traveling of all the second edge's ancestors until it found on that marked as ancestor of the first end. The function returns all the vertices in the cycle.
 -  `dfs_visit`: this function is a recursive function that runs one iteration of DFS on all the neighboors of a given vertice. If the function finds a back edge, it returns an array of the two ends of the back edge. Else, it returns an empty array in size 2.
 -  `bipartitePartition`: this function return the two "sides" of the graph if it is bipartite. If this is a graph with no edges, the graph is clearly bipartite, and the function partitions the graph's vertices by their number.
   Else, the function uses a helper function "bipartite" to check if the graph is bipartite. bipartitePartition sends "bipartite" every uncolored vertice as the source (for case of a disconnected graph). If bipartite returns false (which means that the graph is not bipartite), bipartitePartition will return an array of two empty vectors. Else, bipartitePartition will partition the vertices for two vectors by their color and return an array of the two vectors.
- `bipartite`: this function checks if the graph is bipartite by giving a color to every vertice in the graph. It uses a BFS travel to reach every vertice in the graph, and if the vertice dosen't have a color yet, give it a color. If the vertice have a color, and it's the same color as the vertice's neighboor, the function return false. If the function finishes to give a color to every vertice and dosen't find a vertice that breaks the bipartite condition, the function returns true.
- `getNegativeCycle`: this function detects a negative cycle on a given graph. The function uses bellman- ford to find a vertice from the negative cycle, and marks all its parents on the shortest Path until it get back to the vertice, and then returns a vector of all the vertices on the cycle.

`Graph.hpp`: contains the graph's definition: fields and declarations of its public and the private methods.   
`Graph:cpp`: contains the implementations for the methods:
- `Graph`: defult constructor that initialize the graph's fields defult variables.
- `loadGraph`: this function is the real "constructor" for the graph. It sets the adjacency matrix, the number of edges and vertices and the boolean directed by the matrix it receives. The function checks that the matrix's size is legal, and if the size is not legal, throws an exception. If it is legal, the function sets the number of vertices to be the matrix's size. The function copies the matrix to the adjacency matrix, count the number of edges (every non-zero variable in the matrix) and if the graph is directed (checks it using the helper function "checkDirected"), it sets directed to false and divide the number of edges by 2. Else, it sets isDirectes to true.
- `checkDirected`: helper function for loadGraph that checks if the matrix is symmetrical. Returns false if it is, true if it isn't.
- `getNumOfVertices`: getter for the numOfVertices field.
- `getNumOfEdges`: getter for the numOfEdges field.
- `getAt`: getter for the weight of the edge connected between x and y (given numbers). if there is no edge between them, adjacency_matrix[x][y] will be zero.
- `isDirected`: getter for the directed field.
- `to_string`: returns a string represent the graph in the following format: "Graph with \<numOfVertices\> vertices and \<numOfEdges\> edges."

The other files in the assignment:  
`Demo.cpp`: I added prints of the result of the function "getNegativeCycle", and I changed the demo to match the return values of my functions. Because my functions return vectors and not strings, I added some helper functions to print the vectors.  
`Makefile`: in the Makefile I changed the compiler to g++, because I know how to add debug information to it. I also divided the rules and the targets, because there were more than one file with "main" in a rule.  
`testMain.cpp`: I added this file to run the doctest and the Test.cpp files.  
`Test.cpp`: I added some more tests to the tests I was given. I also added a few functions:
- `testCycle`: this function checks that the vector that "Algorithms::getCycle" returns is realy represents a cycle. It checks that there is an edge between every two following elements in the vector, and also an edge between the first and the last elements.
- `testNegCycle`:this function checks that the vector that "Algorithms::getNegativeCycle" returns is realy represents a negative cycle. It checks that there is an edge between every two following elements in the vector, and also an edge between the first and the last elements, sums the weights of these edges, and checks that the sum is negative.
- `testBipartite`: this function checks that the partition that "Algorithms::bipartitePartition" returns is a legal partition. The function does that by checking that there is no edges between two vertices from the same vector.
