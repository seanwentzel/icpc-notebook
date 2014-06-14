#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

const long long INF = 1<<20;

typedef std::pair<int, int> pii;
typedef std::pair<int, long long> pil;

class PairHasher {
  public:
  std::size_t operator() (const pii &p) const {
    return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
  }
};

int min(int a, int b) {
  return a<b?a:b;
}

void print(std::unordered_map<pii, long long, PairHasher> flow) {
  for (auto it = flow.begin(); it != flow.end(); it++) {
    std::cout<<it->first.first<<" "<<it->first.second<<": "<<it->second<<std::endl;
  }
}

void print(std::vector<int> path) {
  std::cout<<"path ";
  for (int i=0; i<path.size(); i++) {
    std::cout<<path[i]<<" ";
  }
  std::cout<<std::endl;
}

// BFS from source to sink and find a path that has positive capacity
std::pair<std::vector<int>, long long> findpath(
    std::vector<std::vector<pil> > &graph,
    std::unordered_map<pii, long long, PairHasher> &flow,
    int source,
    int sink) {

  // so that we can reverse the path later
  int previous[graph.size()];
  long long previousCapacity[graph.size()];
  bool visited[graph.size()];
  for(int i=0; i<graph.size(); i++) {
    previous[i] = -1;
    visited[i] = false;
  }

  pii coord;
  std::queue<int> q;
  q.push(source);
  bool found = false;
  while(!q.empty()) {
    int cur = q.front();
    q.pop();
    coord.first = cur;

    for (int i=0; i<graph[cur].size(); i++) {
      int next = graph[cur][i].first;
      long long capacity = graph[cur][i].second;
      coord.second = next;
      // if we can't flow through here skip, or
      // if we have already visited this node, skip
      if (visited[next] || capacity - flow[coord] <= 0) 
        continue;
      //std::cout<<"("<<cur<<" "<<next<<"): "<<capacity<<" "<<flow[coord]<<"      "<<capacity - flow[coord]<<std::endl;
      visited[next] = true;
      previous[next] = cur;
      previousCapacity[next] = capacity;

      // traverse this next
      q.push(next);

      // if we have reached our destination construct path and return
      if (next == sink) {
        found =true;
        // to break out of the root loop
        while(!q.empty()) q.pop();
        break;
      }
    }
  }
  if (!found) {
    return std::pair<std::vector<int>, long long>(std::vector<int>(), 0l);
  }

  // let us reconstruct the path from the "previous" array
  int nextPath = sink;
  long long capacity = INF;
  std::vector<int> path;
  path.push_back(nextPath);
  do { 
    coord.first = previous[nextPath];
    coord.second = nextPath;
    capacity = min(capacity, previousCapacity[nextPath] - flow[coord]);
    nextPath = previous[nextPath];
    path.push_back(nextPath);
  } while(nextPath != source);

  // the path is backward so let us reverse that again
  for (int i=0; i<path.size()/2; i++) {
    int temp = path[i];
    path[i] = path[path.size()-i-1];
    path[path.size()-i-1] = temp;
  }

  return make_pair(path, capacity);
}


// find max flow form source to sink. O(VE^2)
// graph: [u][num] = pair<v, capacity>
long long maxflow(
    std::vector<std::vector<pil> > &graph,
    int source,
    int sink) {
  std::unordered_map<pii, long long, PairHasher> flow;

  std::pair<std::vector<int>, int> result;
  std::vector<int> path;
  pii coord;
  do {
    result = findpath(graph, flow, source, sink);
    path = result.first;
    //print(path);
    int pathcapacity = result.second;
    //std::cout<<"capacity "<<pathcapacity<<std::endl;
    for(int i=1; i<path.size(); i++) {
      // forward link
      coord.first = path[i-1];
      coord.second = path[i];
      flow[coord] += pathcapacity;
      // reverse link
      coord.second = path[i-1];
      coord.first = path[i];
      flow[coord] -= pathcapacity;
    }
    //print(flow);
  } while(path.size() != 0);

  long long maxflow = 0;
  coord.first = source;
  for (int i=0; i<graph[source].size(); i++) {
    coord.second = graph[source][i].first;
    maxflow += flow[coord];
  }
  return maxflow;
}

void ae(std::vector<std::vector<pil> > &graph, int from, int to, int weight) {
  graph[from].push_back(pil(to, weight));
  graph[to].push_back(pil(from, 0));
}

int main() {
  std::vector<std::vector<pil> > graph(4);
  ae(graph, 0, 1, 1000);
  ae(graph, 0, 2, 1000);
  ae(graph, 0, 3, 1);
  ae(graph, 1, 2, 1000);
  ae(graph, 2, 3, 1000);
  ae(graph, 1, 3, 1000);

  assert(maxflow(graph, 0, 3) == 2001);
  graph.clear();
  graph.resize(6);
  std::cout<<std::endl;

  // 0 1 2 3 4 5
  // s o p q r t
  ae(graph, 0, 1, 3);
  ae(graph, 0, 2, 3);
  ae(graph, 1, 2, 2);
  ae(graph, 1, 3, 3);
  ae(graph, 2, 4, 2);
  ae(graph, 3, 4, 4);
  ae(graph, 3, 5, 2);
  ae(graph, 4, 5, 3);
  int flow = maxflow(graph, 0, 5);
  assert(flow == 5);

}
