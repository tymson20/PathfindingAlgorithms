# Graphical user interface of pathfinding algorithms
The GUI presents behavior of basic pathfinding algorithms such as Dijkstra or A*. The algorithm can move diagonally or only in 4 directions. Users can draw barriers to create their maze or just simple walls. The application presents a step-by-step expansion of visited nodes and the shortest path at the end.

## Technology used:
- C++
- SFML - 2.6.1
- CMake

## Installation of the required library - SFML
- download a proper version of precompiled binaries based on which platform you want to compile for ([link](https://www.sfml-dev.org/download/sfml/2.6.1/))
- save on your disk
- create a folder named _libraries_ in your project directory
- then create a folder named _SFML_ inside _libraries_
- copy _include_ and _lib_ folders from the library and paste them into the new _SFML_ folder
- make sure that the current project tree looks similar
```
project_directory\
|--libraries\
|  |--SFML\
|     |--include\
|     |--lib\
|...
```

## Screenshots

![Astar diagonal](https://github.com/tymson20/PathfindingAlgorithms/blob/master/assets/images/AstarDiagonal.png)

![Dijkstra diagonal](https://github.com/tymson20/PathfindingAlgorithms/blob/master/assets/images/DijkstraDiagonal.png)

![Astar non-diagonal](https://github.com/tymson20/PathfindingAlgorithms/blob/master/assets/images/AstarNonDiagonal.png)
