#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include "Cell.hpp"

using namespace std;

class Maze
{
public:
    Maze(int, int);
    ~Maze();
    void createCellMatrix();
    void generateMaze();
    // void createAList();
    void solvedMaze(vector<Cell::Edge>);
    void setNeighbors();
    void setWeights();
    void addEdges(Cell *, MinHeap &);
    void resetMaze();
    void union_(Cell::Edge);
    Cell *find_(Cell *cell);
    vector<Cell::Edge> Prims();
    vector<Cell::Edge> Kruskals();

private:
    int m,
        n;
    int s,
        t;
    // the idex represents the vertex and its neighbors
    vector<vector<Cell *>> cellMatrix;
    vector<vector<Cell *>> aList;
    // vector<vector<Cell::Reps *>> representatives;
};
