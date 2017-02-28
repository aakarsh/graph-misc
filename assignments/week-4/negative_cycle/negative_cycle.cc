#include <iostream>
#include <vector>
#include <limits>

using std::vector;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

void print_cycle(vector<int> & prev , int & relaxed_vertex)
{
  std::cerr<<"relaxed-vertex["<<relaxed_vertex<<"]"<<std::endl;
  if(relaxed_vertex < 0)
    return;
  int cur = -1;
  std::cerr<<"Cycle: ("<<relaxed_vertex;
  cur = relaxed_vertex;
  while((cur = prev[cur]) >= 0){
    if(cur == relaxed_vertex)
      break;
    std::cerr<<" "<<cur;
  }
  std::cerr<<")"<<std::endl;
}

/**
 * Iterate through the edge list and relax all relaxable edges
 * returns number of edges relaxed
 */
int relax_edges(vector<vector<int> > & adj, vector<vector<int> > & cost,
                vector<int> & dist, vector<int> &visited,vector<int> & prev , int & relaxed_vertex)
{

  const int max_dist = std::numeric_limits<int>::max();
  int num_relaxations  = 0;

  // Edge(u,v)
  for(int u  = 0; u < adj.size(); u++) {

    if(dist[u] >= max_dist) {
      std::cerr<<"unreachable-vertex:["<<u<<"]"<<std::endl;
      continue;
    }

    visited[u] = true;

    vector<int> neighbours  = adj[u];

    for(int j = 0 ; j < neighbours.size(); j++) {

      int v = neighbours[j];
      int relax_dist =  dist[u] + cost[u][j];

      // Relax Edge
      if( dist[v] > relax_dist ) {

        dist[v] = relax_dist;
        prev[v] = u;
        relaxed_vertex = v;
        num_relaxations++;

        if(debug){
          std::cerr<<num_relaxations<<". relax edge: ("<<u<<","<<v<<") [";
          std::cerr<< cost[u][j] <<"] dist["<< dist[v] <<"]"<<std::endl;
        }

      }
    }
  }

  if(debug)
     std::cerr<<"relax_edges: number_relaxations:["<<num_relaxations<<"]"<<std::endl;

  return num_relaxations;
}

int negative_cycle(vector<vector<int> > &adj,
                   vector<vector<int> > &cost)
{

  // Add a virtual vertex connected to every vertex in the source graph
  for(int i = 0; i < adj.size() -1 ; i++){
    adj[adj.size()-1].push_back(i);
    cost[adj.size()-1].push_back(0);
  }

  // add a virtual node and link it to all vertices
  const int max_dist = std::numeric_limits<int>::max();
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  std::vector<int> prev = vector<int>(adj.size() , -1);
  std::vector<int> visited = vector<int>(adj.size() , false);

  for(int k = 0 ; k < dist.size(); k++) {
    dist[k] = max_dist;
  }

  int src = adj.size() - 1;

  dist[adj.size()-1] = 0;

  if(debug)
    std::cerr<<"src-vertex:["<< src <<"]-"<<std::endl;

    int num_iter = 0;
    int relaxed_vertex = -1;

    while(relax_edges(adj,cost,dist,visited,prev,relaxed_vertex) > 0  &&  num_iter < adj.size())
      num_iter++;

    std::cerr<<"num-iteration:["<<num_iter<<"]"<<std::endl;

    // negative cycle when we have
    // performed relaxation on v'th iteration

    if( num_iter == adj.size()) {
      int relaxed_vertex = -1;
      int num_relaxations  = relax_edges(adj,cost,dist,visited,prev,relaxed_vertex);

      if( num_relaxations > 0) {
        if(debug) {
          print_cycle(prev,relaxed_vertex);
          std::cerr<<"num-iterations["<<num_iter<<"]"<<std::endl;
          std::cerr<<"num-relaxations["<<num_relaxations<<"]"<<std::endl;
        }
        return true;
      }
    }

  return false;
}


int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n+1, vector<int>());
  vector<vector<int> > cost(n+1, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout<<negative_cycle(adj, cost);
}
