#include "Cell.hpp"

Cell::Cell() {}
Cell::Cell(int a, int b)
{
    x = a, y = b;
    // representative = to_string(x) + to_string(y);
}

void Cell::printCell(Cell *cell, int colMax)
{
    if (cell->wall)
        cout << "|";
    else
        cout << " ";

    if (cell->floor)
        cout << "_";
    else
        cout << " ";
    if (cell->y == colMax - 1)
        cout << "|";
}

MinHeap::MinHeap()
{
    Cell cell;
    cell.edge.source = nullptr;
    cell.edge.target = nullptr;
    cell.edge.weight = 0;
    minHeap.push_back(cell.edge);
}

MinHeap::MinHeap(Cell *startCell)
{
    //create place holder for index [0]
    Cell cell;
    cell.edge.source = nullptr;
    cell.edge.target = nullptr;
    cell.edge.weight = 0;
    minHeap.push_back(cell.edge);

    addEdges(startCell);
    // for (int i = 0; i < startCell->edges.size(); i++)
    // {
    //     insert(startCell->edges[i]);
    // }
}

void MinHeap::addEdges(Cell *cell)
{
    // mark the start cell as visited
    cell->visited = true;
    for (int i = 0; i < cell->edges.size(); i++)
    {
        insert(cell->edges[i]);
    }
}

void MinHeap::insert(Cell::Edge e)
{
    if (!e.target->visited)
    {
        // e.target->visited = true;
        minHeap.push_back(e);

        int current = minHeap.size() - 1;
        int parent = current / 2;
        while (minHeap[parent].weight > minHeap[current].weight && current >= 1)
        {
            swap(minHeap[parent], minHeap[current]);

            current = parent;
            parent = parent / 2;
        }
    }
}

Cell::Edge MinHeap::findMin()
{
    return minHeap[1];
}

void MinHeap::deleteMin()
{
    swap(minHeap[1], minHeap[minHeap.size() - 1]);
    minHeap.pop_back();

    int current = minHeap.size() - 1;
    int parent = current / 2;
    while (minHeap[parent].weight > minHeap[current].weight && current >= 1)
    {
        swap(minHeap[parent], minHeap[current]);

        current = current - 1;
        parent = current / 2;
    }
}

void MinHeap::insert_sortedMinHeap(Cell::Edge e)
{
    if (!e.target->visited)
    {
        e.target->visited = true;
        minHeap.push_back(e);

        int current = minHeap.size() - 1;
        int parent = current / 2;
        while (minHeap[parent].weight > minHeap[current].weight && current >= 1)
        {
            swap(minHeap[parent], minHeap[current]);

            current = parent;
            parent = parent / 2;
        }
    }
}

void MinHeap::sortMinHeap(vector<vector<Cell *>> &cellMatrix)
{
    for (int i = 0; i < cellMatrix.size(); i++)
    {
        for (int j = 0; j < cellMatrix[i].size(); j++)
        {
            for (int e = 0; e < cellMatrix[i][j]->edges.size(); e++)
            {
                cellMatrix[i][j]->visited = true;
                insert(cellMatrix[i][j]->edges[e]);

                // //set representatives
                // cellMatrix[i][j]->representative = cellMatrix[i][j];
            }
        }
    }
}
