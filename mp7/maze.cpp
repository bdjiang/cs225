/* Your code here! */
#include "maze.h"
#include <cstdlib>
#include <algorithm>

SquareMaze::SquareMaze() {
}

void SquareMaze::makeMaze(int width, int height) {
  this->width = width;
  this->height = height;

  numCells = width*height;

  //blank cell to mitigate offset
  cells.push_back(Cell(0));
  for (int i = 1; i <= numCells; i++) {
    cells.push_back(Cell(i));
  }

  DisjointSets dset;
	dset.addelements(numCells + 1);

  if (!seed) {
    srand (clock());
    seed = true;
  }

  bool everythingInOne = false;
  while (!everythingInOne) {
    //gets a random cell to use, from 1 to numCells
    int randomCell = rand() % numCells + 1;

    if (randomCell <= width) { //is on the bottom edge of the maze
      if (randomCell == width) { //is the bottom right corner
        continue; //we cannot remove anything from it
      } else { //must remove right wall
        if (dset.find(randomCell) == dset.find(randomCell + 1)) { //if the one to the right is in the same set
          continue;
        } else {
          dset.setunion(randomCell, randomCell + 1);
          cells[randomCell].right = false;
        }
      }
    } else if (randomCell % width == 0) { //is on the right edge
      //no need to check for bottom right since already done
      if (dset.find(randomCell) == dset.find(randomCell - width)) { //if the one below is in the same set
        continue;
      } else {
        dset.setunion(randomCell, randomCell - width);
        cells[randomCell].down = false;
      }
    } else { //it's not on the bottom or the right
      //random number to decide bottom or left wall
      int botOrLeft = rand() % 2;
      if (botOrLeft == 0) {
        if (dset.find(randomCell) == dset.find(randomCell - width)) {
          continue;
        } else {
          dset.setunion(randomCell, randomCell - width);
          cells[randomCell].down = false;
        }
      } else { //borOrLeft = 1
        if (dset.find(randomCell) == dset.find(randomCell + 1)) {
          continue;
        } else {
          dset.setunion(randomCell, randomCell + 1);
          cells[randomCell].right = false;
        }
      }
    }

    //initally say every cell is in one set, use loop to prove wrong
    everythingInOne = true;
    for (int i = 1; i < numCells; i++) {
      if (dset.find(i) != dset.find(i+1)) {
        everythingInOne = false;
        break;
      }
    }

  }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  int index = 1 + x + (y*width);

  if (dir == 0) { //rightward step, x + 1
    if (index % width == 0) { //on the right edge, can't take step
      return false;
    } else {
      return !(cells[index].right);
    }
  }
  if (dir == 1) { //upward step, y + 1
    if (index > numCells - width) { //on the top edge, can't take step
      return false;
    } else {
      return !(cells[index + width].down);
    }
  }
  if (dir == 2) { //leftward step, x - 1
    if ((index - 1) % width == 0) { //on the left edge, can't take step
      return false;
    } else {
      return !(cells[index - 1].right);
    }
  }
  if (dir == 3) { //downward step, y - 1
    if (index <= width) { //on bottom edge, can't take step
      return false;
    } else {
      return !(cells[index].down);
    }
  }

  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  int index = 1 + x + (y*width);
  if(dir == 0) {
    cells[index].right = exists;
  } else if (dir == 1) {
    cells[index].down = exists;
  }
}

vector<int> SquareMaze::solveMaze() {
  int destinationIndex = numCells;


  return vector<int>();
}

PNG* SquareMaze::drawMaze() const {
  return new PNG();
}

PNG* SquareMaze::drawMazeWithSolution() {
  return new PNG();
}
