#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

class pair_compare {
public:
  bool operator() (pair<int,int> & p1 , pair<int,int> & p2)  { return p1.second > p2.second; }
};

typedef std::priority_queue<std::pair<int,int>,std::vector<pair<int,int>>,pair_compare> heap_t;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
  const int max_dist = std::numeric_limits<int>::max();
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  std::vector<int> visited = vector<int>(adj.size() , false);
  
  heap_t edge_heap;

  // all nodes but s will have max dist in the heap
  for (int i = 0; i < adj.size();  i++) {
    if(i == s) dist[i] = 0;;
    edge_heap.push(std::pair<int,int>(i,dist[i]));
  }

  while(!edge_heap.empty()){
    std::pair<int,int> min_vertex = edge_heap.top();
    int u = min_vertex.first;
    edge_heap.pop();
    
    if(visited[u] || dist[u] == max_dist) continue;

    if(debug)
      std::cerr<<"poping vertex["<<u<<"] peri dist = "<<min_vertex.second<<std::endl;    std::vector<int> min_vertex_neighbours = adj[u];
    int edge_num =  0;
    
    for(int i :  min_vertex_neighbours) {      
      int relax_dist = dist[u] + cost[u][edge_num];
      if(debug) {
        std::cerr<<"("<<u<<","<<i<<") "<<cost[u][edge_num]<<std::endl;
        std::cerr<<"dist = "<<dist[i]<<" relaxed distance  = "<<relax_dist<<" cost= "<<cost[u][edge_num]<<std::endl;
      }
      
      if(dist[i] > relax_dist ) {
        if(debug)
         std::cerr<<" pushing  distance ["<<i<<"] : "<<relax_dist<<std::endl;
        // update distance
        edge_heap.push(std::pair<int,int>(i,relax_dist));
        dist[i] = relax_dist;
      }      
      edge_num++;
    }
    visited[u] = true;
  }
  return dist[t] >= max_dist ? -1 : dist[t];
}


int main() {

  int n, m;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  std::cout << distance(adj, cost, s, t);

}
