#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

void distance(vector<vector<int> > &adj, int s, std::vector<int> & dist)
{
  std::queue<int> q = queue<int>();
  const int max_dist = -1;


  q.push(s);
  dist[s] = 0;

  while(!q.empty()) {
    int u  = q.front();
    q.pop();

    for(int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if(dist[v] == max_dist) {  // undiscovered node
        dist[v] = dist[u]+1;     //update distance
        q.push(v);
      }
    }

  }
}

int bipartite(vector<vector<int> > &adj) {
  const int max_dist  = -1;

  for(int i = 0; i <adj.size();i++) {
    std::vector<int> dist = vector<int>(adj.size() , max_dist);
    distance(adj,i,dist);
    for(int j = 0; j < adj.size(); j++){
      if(j == i || dist[j]== -1 || dist[j] == 0)
        continue;

      else if(dist[j] % 2 == 0) {
        std::cout<<"distance between "<<i<<":"<<j<<"="<<dist[j]<<std::endl;
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
