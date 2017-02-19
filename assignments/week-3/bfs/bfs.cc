#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


int distance(vector<vector<int> > &adj, int s, int t)
{  
  std::queue<int> q = queue<int>();
  const int max_dist = -1;
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  
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
  return dist[t];
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

  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);

}
