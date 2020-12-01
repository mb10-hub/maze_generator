#include "Maze.hpp"

Maze::Maze(int x, int y)
{

    cout << "Maze Initialized" << endl;
    // Initialize
    m = x, n = y;

    createCellMatrix();
    generateMaze();
    setNeighbors();
    setWeights();
    // Prims
    vector<Cell::Edge> path_p = Prims();
    solvedMaze(path_p);
    cout << "\nPrim's Algorithm: " << endl;
    generateMaze();

    resetMaze();
    cout << endl;
    //Kruskals
    generateMaze();
    vector<Cell::Edge> path_k = Kruskals();
    solvedMaze(path_k);
    cout << "\nKruskal's Algorithm: " << endl;
    generateMaze();
}

Maze::~Maze()
{
    // deallocate all the pointers

    for (int i = 0; i < cellMatrix.size(); i++)
    {
        for (int j = 0; j < cellMatrix[i].size(); j++)
        {
            cellMatrix[i][j]->edges.clear();
            delete (cellMatrix[i][j]);
        }
    }
    //clear the Alist
    cellMatrix.clear();
}

void Maze::createCellMatrix()
{
    //Build the AList with Cell *

    for (int i = 0; i < m; i++)
    {
        cellMatrix.push_back(vector<Cell *>());
        // representatives.push_back(vector<Cell::Reps *>());

        for (int j = 0; j < n; j++)
        {
            Cell *cell = new Cell(i, j);
            cellMatrix[i].push_back(cell);

            //for reps
            cell->Reps.cell = cell;
            cell->Reps.next = cell;
            // representatives[i].push_back(cell);
        }
    }
}

void Maze::generateMaze()
{
    Cell cell;

    // draw the top border
    // .. the rest gets taken car of with |  & _
    for (int i = 0; i < cellMatrix[0].size(); i++)
    {
        cout << " _";
    }
    cout << endl;
    for (int i = 0; i < cellMatrix.size(); i++)
    {
        for (int j = 0; j < cellMatrix[i].size(); j++)
        {
            cell.printCell(cellMatrix[i][j], n);
        }
        cout << endl;
    }
    cout << " ";
}

void Maze::solvedMaze(vector<Cell::Edge> path)
{
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i].source->x > path[i].target->x)
            path[i].target->floor = false;

        else if (path[i].source->x < path[i].target->x)
            path[i].source->floor = false;

        else if (path[i].source->y > path[i].target->y)
            path[i].source->wall = false;

        else if (path[i].source->y < path[i].target->y)
            path[i].target->wall = false;
    }
}

void Maze::setNeighbors()
{
    //Instead of using Adjacency List, I will keep a list of neighbors for each Cell

    for (int i = 0; i < cellMatrix.size(); i++)
    {

        for (int j = 0; j < cellMatrix[i].size(); j++)
        {

            // if case 1: corner cell -> 2 neighbors;
            if ((i == 0 && j == 0) ||
                (i == 0 && j == cellMatrix[i].size() - 1) ||
                (i == cellMatrix.size() - 1 && j == 0) ||
                (i == cellMatrix.size() - 1 && j == cellMatrix[i].size() - 1))
            {

                if (i == 0 && j == 0)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                }
                else if (i == 0 && j == cellMatrix[i].size() - 1)
                {

                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                }
                else if (i == cellMatrix.size() - 1 && j == 0)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
                }
                else if (i == cellMatrix.size() - 1 && j == cellMatrix[i].size() - 1)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                }
            }
            // if case 2: boarder cell -> 3 neighbors;
            else if ((j == 0) || (j == cellMatrix[i].size() - 1) ||
                     (i == 0) || (i == cellMatrix.size() - 1))
            {
                //Left boarder
                if (j == 0)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                }
                //Right boarder
                else if (j == cellMatrix[i].size() - 1)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                }
                //Top boarder
                else if (i == 0)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                }
                //Bottom boarder
                else if (i == cellMatrix.size() - 1)
                {
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                    cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
                }
            }
            // if case 3: middle cell -> 4 neighbors;
            else
            {
                cellMatrix[i][j]->neighbors.push_back(cellMatrix[i - 1][j]);
                cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j - 1]);
                cellMatrix[i][j]->neighbors.push_back(cellMatrix[i + 1][j]);
                cellMatrix[i][j]->neighbors.push_back(cellMatrix[i][j + 1]);
            }
        }
    }
}

void Maze::setWeights()
{
    Cell cell;

    int random_weight;
    srand(time(NULL));

    for (int i = 0; i < cellMatrix.size(); i++)
    {

        for (int j = 0; j < cellMatrix[i].size(); j++)
        {
            //create edges to all neighbors @ weight 1
            for (int e = 0; e < cellMatrix[i][j]->neighbors.size(); e++)
            {

                cell.edge.source = cellMatrix[i][j];
                cell.edge.target = cellMatrix[i][j]->neighbors[e];
                random_weight = rand() % 20 + 1;
                cell.edge.weight = random_weight;
                // cell.edge.weight = 1;

                cellMatrix[i][j]->edges.push_back(cell.edge);
            }
        }
    }
}

void Maze::addEdges(Cell *cell, MinHeap &minHeap)
{
}

vector<Cell::Edge> Maze::Prims()
{
    //Initialize vector of edges
    vector<Cell::Edge> path;
    // queue<Cell::Edge> q;
    Cell *cell;

    // choose random cell(vertex) and add all its edges to the minHeap
    MinHeap MinHeap(cellMatrix[0][0]);
    // call min heap to choose the shortest edge.
    path.push_back(MinHeap.findMin());
    // q.push(MinHeap.findMin());
    cell = MinHeap.findMin().target;
    MinHeap.deleteMin();

    while (MinHeap.minHeap.size() > 1)
    {

        // add the target cell(vertex) and add all its edges to the minHeap
        // MinHeap.addEdges(MinHeap.findMin().target);
        MinHeap.addEdges(cell);

        if (MinHeap.findMin().target->visited == false)
        {
            //get the min of from minHeap and push it to path and queue.
            path.push_back(MinHeap.findMin());
        }
        // q.push(MinHeap.findMin());
        cell = MinHeap.findMin().target;

        //delete the min
        MinHeap.deleteMin();
        // q.pop();
    }

    return path;
}

void Maze::resetMaze()
{
    for (int i = 0; i < cellMatrix.size(); i++)
    {
        for (int j = 0; j < cellMatrix[i].size(); j++)
        {
            cellMatrix[i][j]->floor = true;
            cellMatrix[i][j]->wall = true;
            cellMatrix[i][j]->visited = false;
        }
    }
}

void Maze::union_(Cell::Edge e)
{
    Cell *rep_of_source = find_(e.source);
    Cell *rep_of_target = find_(e.target);
    rep_of_source->Reps.next = rep_of_target;
}

Cell *Maze::find_(Cell *cell)
{
    if (cell->Reps.next == cell)
        return cell->Reps.next;
    return find_(cell->Reps.next);
}

vector<Cell::Edge> Maze::Kruskals()
{
    vector<Cell::Edge> path;
    Cell *representative_target;
    Cell *representative_source;

    MinHeap MinHeap;
    MinHeap.sortMinHeap(cellMatrix);

    Cell *rep_source;
    Cell *rep_target;

    while (MinHeap.minHeap.size() > 1)
    {
        //rep of target
        // representative_target = find_(MinHeap.findMin().target);
        rep_source = find_(MinHeap.findMin().source);
        // // rep of source
        // representative_source = find_(MinHeap.findMin().source);
        rep_target = find_(MinHeap.findMin().target);

        if (rep_target != rep_source)
        {
            path.push_back(MinHeap.findMin());
            union_(MinHeap.findMin());
        }
        MinHeap.deleteMin();
    }

    return path;
}
