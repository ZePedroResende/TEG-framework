//
// Created by resende on 11/26/19.
//

#ifndef SCHEDULER_MASTER_GRAPH_H
#define SCHEDULER_MASTER_GRAPH_H

#include <vector>

struct Edge {
  int src, dest;
};

class Graph
{
public:
  std::vector<std::vector<int>> adjList;

  Graph(std::vector<Edge> const &edges, int N)
  {
    adjList.resize(N);

    for (auto &edge: edges)
    {
      adjList[edge.src].push_back(edge.dest);
    }
  }
};
#endif // SCHEDULER_MASTER_GRAPH_H
