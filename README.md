# API Project   
![grade](https://img.shields.io/badge/Grade-100%25-green)

The goal of the project is to manage a ranking between weighted direct graphs.
- The leaderboard keeps track of the k "best" graphs.

The program receives input:
- two parameters, once (on the first line of the file, separated by space)
    - d: the number of graph nodes
    - k: the length of the ranking
- A sequence of commands between
    - AddGraph [adjacency-matrix]
    - TopK

d, k and the number of graphs are representable with 32-bit integers.
#
AddGraph requires to add a graph to those considered to compute the ranking. It is followed by the adjacency matrix of the graph itself, printed line by line, with the elements separated by commas.

#
TopK asks the program to print the integer indices of the k graphs having the smallest k values ​​using the following metric: 
- Sum of the shortest paths between node 0 and all the other nodes of the graph reachable from 0.

#


##
> To see the complete requirements (Italian) -> [Project presentation](specifica.pdf)