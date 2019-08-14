/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNVISITED");
    }
    vector<Edge> edges = graph.getEdges();
    int min = edges[0].weight;
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNVISITED");
      if (edges[i].weight < min) {
        min = edges[i].weight;
      }
    }

    std::queue<Vertex> visited;

    Vertex current = graph.getStartingVertex();
    graph.setVertexLabel(current, "VISITED");
    visited.push(current);

    while(!visited.empty()) {
      current = visited.front();
      visited.pop();
      vector<Vertex> adjacent = graph.getAdjacent(current);
      for (size_t i = 0; i < adjacent.size(); i++) {
        if (graph.getVertexLabel(adjacent[i]) == "UNVISITED") {
          graph.setVertexLabel(adjacent[i], "VISITED");
          visited.push(adjacent[i]);
          graph.setEdgeLabel(current, adjacent[i], "DISCOVERY");
        }

        if (graph.getEdgeLabel(current, adjacent[i]) == "UNVISITED") {
          graph.setEdgeLabel(current, adjacent[i], "CROSS");
        }
      }
    }

    for (size_t i = 0; i < edges.size(); i++) {
      if (edges[i].weight == min) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "MIN");
      }
    }

    return min;

}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNVISITED");
    }

    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNVISITED");
    }

    std::queue<Vertex> visited;

    Vertex current = start;
    graph.setVertexLabel(current, "VISITED");
    visited.push(current);
    unordered_map <Vertex, Vertex> parent;

    while(!visited.empty()) {
      current = visited.front();
      visited.pop();
      vector<Vertex> adjacent = graph.getAdjacent(current);
      for (size_t i = 0; i < adjacent.size(); i++) {
        if (graph.getVertexLabel(adjacent[i]) == "UNVISITED") {
          graph.setVertexLabel(adjacent[i], "VISITED");
          visited.push(adjacent[i]);
          pair <Vertex, Vertex> vertexPairs (adjacent[i], current);
          parent.insert(vertexPairs);
          graph.setEdgeLabel(current, adjacent[i], "DISCOVERY");
        }

        if (graph.getEdgeLabel(current, adjacent[i]) == "UNVISITED") {
          graph.setEdgeLabel(current, adjacent[i], "CROSS");
        }
      }
    }

    int distance = 0;
    Vertex backtrace = end;
	  while (start != backtrace) {
      graph.setEdgeLabel(backtrace, parent[backtrace], "MINPATH");
      backtrace = parent[backtrace];
      distance++;
    }
	  return distance;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    vector<Vertex> vertices = graph.getVertices();
    std::sort(edges.begin(), edges.end());

    int edgesIn = 0;

    DisjointSets djs;
    djs.addelements((int)edges.size());

    for (size_t i = 0; i < edges.size(); i++) {
      if (edgesIn >= (int)vertices.size() - 1) {
        break;
      }
      if (djs.find(edges[i].source) != djs.find(edges[i].dest)) {
        djs.setunion(edges[i].source, edges[i].dest);
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
      }
    }
}
