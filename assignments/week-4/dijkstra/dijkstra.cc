#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

class pair_compare
{
public:
  bool operator() (pair<int,int> & p1 , pair<int,int> & p2)
  {
    return p1.second < p2.second;
  }
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
  const int max_dist = adj.size() * adj.size();
  std::vector<int> dist = vector<int>(adj.size() , max_dist);
  std::pair<int,int> shortest;

  std::priority_queue<std::pair<int,int>,std::vector<pair<int,int>>,pair_compare>  edge_heap;

  for (int i = 0; i < adj.size();  i++) {
    std::pair<int,int> vertex(i,max_dist);
    edge_heap.push(vertex);    
    
  }

  return -1;
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
