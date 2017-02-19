#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

#ifdef DEBUG
const bool debug = true;
#endif

#ifndef DEBUG
const bool debug = false;
#endif

enum visit_state { white, grey ,black };

int dfs_visit(vector<vector<int> > &adj, vector<int>& visited, vector<int> & post, int x,int & time)
{
  if(debug)
    std::cout<<"Visiting:"<<x<<"Time["<<time<<"]"<<std::endl;

  visited[x]  = grey;
  vector<int> neighbours = adj[x];

  for(int neighbour : neighbours) {
    if(visited[neighbour] == white ) {
      dfs_visit(adj,visited,post,neighbour,time);
    } else { //visited neighbour
      if(visited[neighbour] == grey) {
        if(debug)
          std::cout<<"Found predecessor still visiting"<<std::endl;
      }
      else if(post[neighbour] < post[x] ) {
        if(debug)
          std::cout<<"Found backedge"<<std::endl;
      }
    }
  }

  visited[x] = black;
  post[x] = time++;
  if(debug)
    std::cout<<x<<" done @["<<time<<"]"<<std::endl;

}

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
}

vector<int> toposort(vector<vector<int> > adj) {
  int n = adj.size();
  vector<int> used(n, 0);
  vector<int> order(n);

  vector<int> visited(n);
  vector<int> post(n);
  int time = 0;

  for(int i =0; i < n; i++){
    if(visited[i] == white)
      dfs_visit(adj,visited,post,i,time);
  }

  for(int i = 0; i< n; i++) {
    order[n - 1 - post[i]] = i; // The time at which vertex - i finishes
    if(debug)
      std::cout<<"["<<i<<"]"<<" "<<post[i]<<std::endl;
  }


  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
