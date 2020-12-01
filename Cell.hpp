#include <iostream>
#include <vector>

using namespace std;

class Cell
{
public:
    struct Edge
    {
        Cell *source;
        Cell *target;
        int weight;
    } edge;

    struct Representatives
    {
        Cell *cell;
        Cell *next;
    } Reps;

    Cell();
    Cell(int a, int b);
    void printCell(Cell *, int);

    //variables
    int x, y;
    bool visited = false;
    bool wall = true;
    bool floor = true;
    //vecotors of neighbors and edges
    vector<Cell *> neighbors;
    vector<Edge> edges;

private:
};

class MinHeap
{
public:
    MinHeap();
    MinHeap(Cell *startCell);
    void insert(Cell::Edge);
    void deleteMin();
    void addEdges(Cell *);
    void sortMinHeap(vector<vector<Cell *>> &);
    void insert_sortedMinHeap(Cell::Edge);

    vector<Cell::Edge> minHeap;
    Cell::Edge findMin();

    // private:
    //     vector<Cell::Edge> minHeap;
};