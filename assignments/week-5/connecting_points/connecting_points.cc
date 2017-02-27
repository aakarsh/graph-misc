#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>


using std::priority_queue;
using std::vector;
using std::pair;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif


void init_distances(vector<vector<double>> & dist, vector<std::pair<int,int>> & vertices )
{
  int n = vertices.size();
  for(int i = 0 ; i < n; i++ ) {
    for(int j = 0 ; j <= i; j++) {
      std::pair<int,int> diffs;
      diffs.first = pow(vertices[i].first-vertices[j].first,2);
      diffs.second = pow(vertices[i].second-vertices[j].second,2);
      dist[i][j] =  dist[j][i] = sqrt(diffs.first+diffs.second);
    }
  }
}

class pair_compare {
public:
  bool operator() (pair<int,double> & p1 , pair<int,double> & p2)  { return p1.second > p2.second; }
};

typedef std::priority_queue<std::pair<int,double>,std::vector<pair<int,double>>,pair_compare> heap_t;

double clustering(vector<int> x, vector<int> y, int k) {

  const double inf = std::numeric_limits<double>::max();
  double retval = 0.0;
  int n = x.size();

  vector<std::pair<int,int>> vertices(n,pair<int,int>());
  vector<int> visited(n,0);
  vector<int> parent(n,-1);
  vector<double> cost(n,inf);

  for(int i  = 0 ; i < n ; i++) {
    vertices[i].first  = x[i];
    vertices[i].second = y[i];
  }

  vector<vector<double>> dist(n,vector<double>(n,inf));
  init_distances(dist,vertices);

  for(int i = 0; i < n;i++)
    for(int j = 0 ; j < n; j++)
      if(debug)
        std::cerr<<"dist["<<i<<"]["<<j<<"]  = "<<dist[i][j]<<std::endl;

  heap_t vertex_queue;

  for(int i = 0; i < n; i++) {
    double cost  = i == 0 ? 0 : inf;
    vertex_queue.push(std::pair<int,double>(i,cost));
  }

  cost[0] = 0;

  while(!vertex_queue.empty()) {

    std::pair<int,double> min_vertex_pair =  vertex_queue.top();
    vertex_queue.pop();

    int v = min_vertex_pair.first;
    double c = min_vertex_pair.second;

    if( visited[v] )
        continue;
    retval+= c;

    if(debug){
      int x = vertices [v].first;
      int y = vertices[v].second;
      std::cerr<<"popped["<<v<<"]"<<"("<<x <<","<<y<<")"<<":"<<c<<std::endl;
      std::cerr<<"retval = ["<<retval<<"]"<<std::endl;
    }

    visited[v] = 1;

    // Through complete graph
    for(int i = 0; i < n; i++) {
      if(i!=v && cost[i] > dist[v][i]) {
        cost[i] = dist[v][i];
        parent[i] = v;
        //update cost in heap
        if(debug)
          std::cerr<<"pushing "<<i<<":"<<dist[v][i]<<std::endl;
        vertex_queue.push(pair<int,double>(i,dist[v][i]));
      }
    }
  }

  return retval;
}


int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
