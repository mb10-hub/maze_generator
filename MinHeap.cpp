#include "MinHeap.hpp"

// MinHeap::MinHeap(Cell *startCell)
// {
//     //create place holder for index [0]
//     Cell cell;
//     cell.edge.source = nullptr;
//     cell.edge.target = nullptr;
//     cell.edge.weight = 0;
//     minHeap.push_back(cell.edge);

//     for (int i = 0; i < startCell->edges.size(); i++)
//     {
//         insert(startCell->edges[i]);
//     }
// }

// void MinHeap::insert(Cell::Edge e)
// {
//     minHeap.push_back(e);

//     int parent = minHeap.size() / 2;
//     int current = minHeap.size() - 1;
//     int temp = 0;
//     while (minHeap[parent].weight > minHeap[current].weight || current <= 1)
//     {
//         swap(minHeap[parent], minHeap[current]);

//         current = parent;
//         parent = parent / 2;
//     }
// }
