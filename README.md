# System Programming 2 Assignment 1
for this assignment I used 2 classes:  
`Algorithms`: contains static functions (like a library)  
`Graph`: represent a graph and contains the graph's fields and methods  

each one of the classes has a hpp and a cpp files.  

`Algorithms.hpp`: contains the declarations of the public and the private functions.  
`Algorithms.cpp`: contains the implementations for the functions:
- `isConnected`: this function checks the connectivity of a given graph. if it is a directed graph, the function checks a strong connectivity. this function uses the function "traverse", by sending to the function each one of the vertices in the graph. after every call for "traverse", isConnected checks if one of the vertices havn't been visited. if such a vertice exist, the function return false. if the function didn't find such a vertice in all the iterations, the function returns true.    
- `traverse`: the function receives a source node, a graph and an array of booleans. the function marks every vertice as "visited" in the array if the node is reachable from the source.

 - `shortestPath`: the function starts with a call for "getNegativeCycle" to make sure that there is no negative cycle in the graph. then it checks the shortestPath from the start vertice to the end vertice (which it receives) using dijkstra's algorithm. the function returns a vector of all the vertices in the path.
 - 
