#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <queue>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  masterImage_ = png;
  current_ = start;
  visited_[visited_.size()] = current_;
  tolerance_ = tolerance;

  addNeighbors(current_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  toVisit_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point returnPoint = current_;
  current_ = toVisit_.top();
  toVisit_.pop();

  addNeighbors(current_);

  return returnPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return toVisit_.empty();
}

void DFS::addNeighbors(Point & point) {
  int right = point.x + 1;
  int down = point.y + 1;
  int left = point.x - 1;
  int up = point.y - 1;

  if (right < (int)masterImage_.width()) {
    bool canAdd = true;
    Point* possiblePoint = new Point(right, point.y);

    for (int i = 0; i < (int)visited_.size(); i++) {
      if (visited_[i].x == possiblePoint -> x && visited_[i].y == possiblePoint -> y) {
        canAdd = false;
      }
    }

    if (canAdd) {
      toVisit_.push(*possiblePoint);
    }

  }
  if (down < (int)masterImage_.height()) {
    bool canAdd = true;
    Point* possiblePoint = new Point(point.x, down);

    for (int i = 0; i < (int)visited_.size(); i++) {
      if (visited_[i].x == possiblePoint -> x && visited_[i].y == possiblePoint -> y) {
        canAdd = false;
      }
    }

    if (canAdd) {
      toVisit_.push(*possiblePoint);
    }
  }
  if (left >= 0) {
    bool canAdd = true;
    Point* possiblePoint = new Point(left, point.y);

    for (int i = 0; i < (int)visited_.size(); i++) {
      if (visited_[i].x == possiblePoint -> x && visited_[i].y == possiblePoint -> y) {
        canAdd = false;
      }
    }

    if (canAdd) {
      toVisit_.push(*possiblePoint);
    }
  }
  if (up >= 0) {
    bool canAdd = true;
    Point* possiblePoint = new Point(point.x, up);

    for (int i = 0; i < (int)visited_.size(); i++) {
      if (visited_[i].x == possiblePoint -> x && visited_[i].y == possiblePoint -> y) {
        canAdd = false;
      }
    }

    if (canAdd) {
      toVisit_.push(*possiblePoint);
    }
  }
}
