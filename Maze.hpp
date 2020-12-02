#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include "Cell.hpp"
#include "Solve.hpp"

using namespace std;

class Maze
{
public:
    Maze(int, int);
    ~Maze();
    void createCellMatrix();
    void generateMaze();
    void generateSolvedMaze();
    // void createAList();
    void solvedMaze(vector<Cell::Edge>);
    void setNeighbors();
    void setWeights();
    void addEdges(Cell *, MinHeap &);
    void resetMaze();
    void resetVisited();
    void union_(Cell::Edge);
    void setPath(vector<Cell *> path, vector<vector<Cell *>>);
    Cell *find_(Cell *cell);
    vector<Cell::Edge> Prims();
    vector<Cell::Edge> Kruskals();
    vector<vector<Cell *>> getMaze();

    //variables
    int m,
        n;
    // Cell *Start = cellMatrix[0][0], *target = cellMatrix[m - 1][n - 1];
    // the idex represents the vertex and its neighbors
    vector<vector<Cell *>> cellMatrix;
    vector<vector<Cell *>> aList;
    // vector<vector<Cell::Reps *>> representatives;
};

struct Node
{
    Cell *cell;
    vector<Node *> child;
    Node *parent;
};

class Solve
{
public:
    Solve();

    vector<Cell *> dfsPathFromTo(Cell *, Cell *, vector<vector<Cell *>> &);
    Node *newNode(Cell *cell, Node *parent_index);
    void children_true(Node *curr);
    bool makesPath(Cell *, Cell *);

    //variables
    // Cell *Start, *Target;
};
