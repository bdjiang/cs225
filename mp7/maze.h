/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"

#include <vector>

using namespace std;
using namespace cs225;

static bool seed = false;

class SquareMaze {
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();

    struct Cell {
      Cell(int number) {
        right = true;
        down = true;
        labelNumber = number;
      }

      int labelNumber;
      bool right;
      bool down;
    };

  private:
    int width;
    int height;
    int numCells;

    vector<Cell> cells;

};
#endif
