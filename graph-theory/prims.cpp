// Author: Yaseen Hamdulay
// Prim's Algorithm
//
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cassert>

using namespace std;

#define TEST true

struct edge {
  edge(int parent, int child, int weight);
  int parent;
  int child;
  int weight;
};

edge::edge(int parent, int child, int weight) : parent(parent), child(child), weight(weight) {}

bool operator<(const edge &lhs, const edge &rhs) {
  return rhs.weight < lhs.weight;
}

/**
 * @param adjacency_list input graph
 * @param start starting point of msp
 * @return adjacency list of points in the MSP
 */
vector<vector<edge> > prims(vector<vector<edge> > adjacency_list, int start) {
  // +1 so it doesn't matter if we're 0 or 1 childed as long as we're consistent
  vector<vector<edge> > result(adjacency_list.size()+1, vector<edge>());
  vector<bool> visited(adjacency_list.size()+1, false);

  priority_queue<edge> q;
  for(edge &e: adjacency_list[start]) {
    q.push(e);
  }

  while(!q.empty()) {
    edge cur = q.top();
    q.pop();
    if (visited[cur.child])
      continue;
    visited[cur.child] = true;
    result[cur.parent].push_back(cur);

    for (edge &child: adjacency_list[cur.child]) {
      if (!visited[child.child]) {
        q.push(child);
      }
    }
  }
  return result;
}

#if TEST
int main() {
  vector<vector<edge> > graph(3, vector<edge>());
  graph[0].push_back(edge(0, 1, 6));
  graph[0].push_back(edge(0, 2, 2));
  graph[2].push_back(edge(2, 1, 3));

  vector<vector<edge> > result = prims(graph, 0);
  assert(result[0][0].child == 2);
  assert(result[0][0].weight == 2);
  assert(result[0].size() == 1);
  assert(result[2].size() == 1);
}
#endif
