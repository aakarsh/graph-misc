#include <iostream>
#include <vector>
#include <limits>

using std::vector;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
  
  const int max_dist = std::numeric_limits<int>::max();
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  std::vector<int> prev = vector<int>(adj.size() , -1);
  std::vector<int> visited = vector<int>(adj.size() , false);

  bool num_relaxations = 0;

  for(int i = 0 ; i < adj.size() ; i++) {

    if(visited[i]) {
      if(debug) std::cerr<<"skip-vertex:["<<i<<"]"<<std::endl;
      continue;
    }

    for(int k = 0 ; k < dist.size(); k++) {
      dist[k] = k == i ? 0 : max_dist;
    }

    if(debug)
      std::cerr<<"src-vertex:["<<i<<"]"<<std::endl;

    int num_iter = 0;
    bool relaxed_an_edge = true;
    int relax_time = 0;

    while(relaxed_an_edge && num_iter < adj.size()  ) {

      relaxed_an_edge = false;
      num_iter++;

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

          if(debug){
            std::cerr<<num_iter<<"."<<num_relaxations;
            std::cerr<<" check: ("<<u<<","<<v<<") ["<<cost[u][j]<<"]";
            std::cerr<<"dist["<<dist[v]<<"]"<<"] relax["<<relax_dist<<"]"<<std::endl;
          }

          // relax edge
          if(dist[v] > relax_dist && dist[u] != max_dist) {

            relaxed_an_edge = true;
            dist[v] = relax_dist;
            prev[v] = u;
            num_relaxations++;
            relax_time = num_iter;

            if(debug)
              std::cerr<<num_iter<<"."<<num_relaxations<<". relax edge: ("<<u<<","<<v<<") ["<<cost[u][j]<<"] dist["<<dist[v]<<"]"<<std::endl;
          }
        }
      }
    }

    if(relax_time == num_iter && num_iter == adj.size()) {      
      if(debug){
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
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
