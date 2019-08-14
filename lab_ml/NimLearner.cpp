/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"

using namespace std;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {

  for (int i = (int)startingTokens; i >= 0; i--) {
    string label = "p1-" + to_string(i);
    g_.insertVertex(label);

    label = "p2-" + to_string(i);
    g_.insertVertex(label);
  }

  string labelStart = "p1-" + to_string((int)startingTokens);
  startingVertex_ = g_.getVertexByLabel(labelStart);

  for (int i = (int)startingTokens; i > 0; i--) {
    string label = "p1-" + to_string(i);
    Vertex p1 = g_.getVertexByLabel(label);
    label = "p2-" + to_string(i-1);
    Vertex p11 = g_.getVertexByLabel(label);
    g_.insertEdge(p1, p11);
    g_.setEdgeWeight(p1, p11, 0);
    if (i > 1) {
      label = "p2-" + to_string(i-2);
      Vertex p12 = g_.getVertexByLabel(label);
      g_.insertEdge(p1, p12);
      g_.setEdgeWeight(p1, p12, 0);
    }

    label = "p2-" + to_string(i);
    Vertex p2 = g_.getVertexByLabel(label);
    label = "p1-" + to_string(i-1);
    Vertex p21 = g_.getVertexByLabel(label);
    g_.insertEdge(p2, p21);
    g_.setEdgeWeight(p2, p21, 0);
    if (i > 1) {
      label = "p1-" + to_string(i-2);
      Vertex p22 = g_.getVertexByLabel(label);
      g_.insertEdge(p2, p22);
      g_.setEdgeWeight(p2, p22, 0);
    }
  }

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;

  Vertex current = startingVertex_;

  string labelEnd1 = "p1-0";
  string labelEnd2 = "p2-0";

  while((g_.getVertexLabel(current) != labelEnd1) &&
        (g_.getVertexLabel(current) != labelEnd2)) {
    vector<Vertex> adjacent = g_.getAdjacent(current);

    int whichToGo = rand() % (int)adjacent.size();
    Vertex newCurrent = adjacent[whichToGo];

    Edge edge = g_.getEdge(current, newCurrent);
    path.push_back(edge);
    current = newCurrent;
  }

  return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  string p1win = "p2-0";
  string p2win = "p1-0";

  Edge winningEdge = path.back();
  if (g_.getVertexLabel(winningEdge.dest) == p1win) {
    //std::cout << "winner was p1! how do we know? " << g_.getVertexLabel(winningEdge.dest) << std::endl;
    for (int i = 0; i < (int)path.size(); i++) {
      if (g_.getVertexLabel(path[i].source).substr(0,2) == "p1") {
        g_.setEdgeWeight(path[i].source, path[i].dest, path[i].weight+1);
      } else {
        g_.setEdgeWeight(path[i].source, path[i].dest, path[i].weight-1);
      }
    }
  } else {
    //std::cout << "winner was p2! how do we know? " << g_.getVertexLabel(winningEdge.dest) << std::endl;
    for (int i = 0; i < (int)path.size(); i++) {
      if (g_.getVertexLabel(path[i].source).substr(0,2) == "p2") {
        g_.setEdgeWeight(path[i].source, path[i].dest, path[i].weight+1);
      } else {
        g_.setEdgeWeight(path[i].source, path[i].dest, path[i].weight-1);
      }
    }
  }
}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
