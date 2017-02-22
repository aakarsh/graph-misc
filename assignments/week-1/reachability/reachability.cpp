#include <iostream>
#include <vector>

using std::vector;
using std::pair;

const bool debug = false;

enum visit_state { white, grey ,black };

int dfs_visit(vector<vector<int> > &adj, vector<int>& visited, int x)
{
  if(debug) 
    std::cout<<"Visiting:"<<x<<std::endl;
  
  visited[x]  = grey;
  vector<int> neighbours = adj[x];
  
  for(int neighbour : neighbours) {
    if(visited[neighbour] == white ) {
      dfs_visit(adj,visited,neighbour);
    }
  }
  
  visited[x] = black;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  vector<int> visited(adj.size());
  dfs_visit(adj,visited,x);
  return visited[y] == black;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
