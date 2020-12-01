#include <iostream>
#include <vector>
#include "Maze.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Pass two Numbers for the size of the Maze: " << endl;
        exit(1);
    }
    int m, n;
    m = stoi(argv[1]);
    n = stoi(argv[2]);

    Maze maze(m, n);

    // cout << "stop" << endl;
}
