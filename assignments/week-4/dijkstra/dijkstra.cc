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

class pair_compare
{
public:
  bool operator() (pair<int,int> & p1 , pair<int,int> & p2)
  {
    return p1.second > p2.second;
  }
};

typedef std::priority_queue<std::pair<int,int>,std::vector<pair<int,int>>,pair_compare> heap_t;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
  const int max_dist = std::numeric_limits<int>::max();
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  std::vector<int> visited = vector<int>(adj.size() , false);
  std::pair<int,int> shortest;

  heap_t edge_heap;

  // 1. Set all distance pairs to inf and
  //    distance from  source to zero  
  for (int i = 0; i < adj.size();  i++) {
    if(i == s){
      dist[i] = 0;
    }
    std::pair<int,int> vertex(i,dist[i]);
    edge_heap.push(vertex);
  }

  while(!edge_heap.empty()){
    std::pair<int,int> min_vertex = edge_heap.top();

    int u = min_vertex.first;         
    edge_heap.pop();

    if(visited[u]) continue;

    if(debug)
      std::cout<<"poping vertex["<<min_vertex.first<<"] peri dist = "<<min_vertex.second<<std::endl;

    std::vector<int> min_vertex_neighbours = adj[u];
    
    int edge_num =  0;
    for(int i :  min_vertex_neighbours) {
      int relaxed_distance = dist[u] + cost[u][edge_num];

      if(debug) {
        std::cout<<"("<<u<<","<<i<<") "<<cost[u][edge_num]<<std::endl;

        std::cout<<"dist = "<<dist[i]<<" relaxed distance  = "<<relaxed_distance<<" cost= "<<cost[u][edge_num]<<std::endl;
      }
      
      if(dist[i] > relaxed_distance ) {
        if(debug)
         std::cout<<" pushing  distance ["<<i<<"] : "<<relaxed_distance<<std::endl;
        // update distance
        edge_heap.push(std::pair<int,int>(i,relaxed_distance));
        dist[i] = relaxed_distance;
        
      }
      edge_num++;
    }

    visited[u] = true;
  }

  if(dist[t] >= max_dist){
    dist[t] = -1;
  }

  return dist[t];
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
