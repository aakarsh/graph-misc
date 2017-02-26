#include <iostream>
#include <vector>

using std::vector;
using std::pair;

const bool debug = false;

enum visit_state { white, grey ,black };

int dfs_visit(vector<vector<int> > &adj, vector<int>& visited, vector<int> & post, int x,int & time,int& nback_edges)
{
  if(debug) 
    std::cerr<<"Visiting:"<<x<<"Time["<<time<<"]"<<std::endl;
  
  visited[x]  = grey;
  vector<int> neighbours = adj[x];

  for(int neighbour : neighbours) {
    if(visited[neighbour] == white ) {
      dfs_visit(adj,visited,post,neighbour,time,nback_edges);
    } else { //visited neighbour
      if(visited[neighbour] == grey) {
        if(debug)
          std::cerr<<"Found predecessor still visiting"<<std::endl;
        nback_edges++;
      }      
      else if(post[neighbour] < post[x] ) {
        if(debug)
          std::cerr<<"Found backedge"<<std::endl;
        nback_edges++;
      }
    }
  }
  
  visited[x] = black;
  post[x] = time++;      
  if(debug)
    std::cerr<<x<<" done @["<<time<<"]"<<std::endl;
    
}


int acyclic(vector<vector<int> > &adj)
{
  vector<int> visited(adj.size());
  vector<int> post(adj.size());
  int time = 0;
  int nback_edges = 0;
  
  for(int i =0; i < adj.size(); i++){
    if(visited[i] == white)
      dfs_visit(adj,visited,post,i,time,nback_edges);
  }
  
  if(debug)
    std::cerr<<"Number of Back Edges:"<<nback_edges<<std::endl;
  
  return nback_edges != 0;
}


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    if(debug)
      std::cerr<<"Adding edge "<<(x-1)<<"->"<<(y-1)<<std::endl;
  }
  std::cout << acyclic(adj);
}
