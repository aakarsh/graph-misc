#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstdlib>

using namespace std;

enum graph_store { adjacency_list , adjacency_matrix } ;
enum node_color { white, black };
enum node_visited { visited, visiting, unvisited };

const bool debug = false;

class node {
  
protected:
  int id;
  void* data;
  node_color color;
  vector<node*> neighbours;
  node_visited visited;

public:
  node(int id, void* ptr): node(id,ptr,white){}
  node(int id, void* ptr, node_color c): id(id), data(ptr),color(c),visited(unvisited){}
  friend class graph;
  
  void mark_visting()   { 
    this->visited = visiting;  
    if(debug)
      cout<<"visiting:"<< id <<endl;
  }  
  void mark_unvisited() { 
    this->visited = unvisited;
  }
  
  void mark_visited()   { 
    this->visited = visited; 
    if(debug)
      cout<<"done:"<< id<<endl;
  }
  

  bool unvisitedp()     { return this->visited == unvisited; }
  
};


class graph {
public:
  int nedges;
  int nvertices;
private:  
  int size;
  graph_store type;
  vector<node*> nodes;  

public:
  graph(int n,graph_store st): size(n), type(st) {
    switch(st){
    case adjacency_list:
      for(int i = 0 ; i < n ; i++){
        nodes.push_back(new node(i,NULL, white));
      }
      break;
    case adjacency_matrix:

      break;
    default:;
    }
  }

  void set_node_data(int n,void* data){
    nodes[n]->data = data;
  }

  void add_mutual_edge(int a, int b) {
    nodes[a]->neighbours.push_back(nodes[b]);
    nodes[b]->neighbours.push_back(nodes[a]);

  }

  void mark_unvisited() {
    for(node*  n : nodes){
      n->mark_unvisited();
    }
  }

  void dfs_visit(node* a) {    
    a->mark_visting();    
    for( node* n : a->neighbours )       
      if(n->unvisitedp()) 
        dfs_visit(n);    
    a->mark_visited();
  }
  
  int reachable(int a, int b) {
    this->mark_unvisited();
    this->dfs_visit(nodes[a]);    
    return !(nodes[b]->unvisitedp());
  }

  int count_components() {
    
    this->mark_unvisited();
    int count = 0;

    for(node* node : nodes) {
      if(node->unvisitedp()) {
          count++;
          dfs_visit(node);
      }    
    }
    return count;
  }

  static graph* parse_graph() {
    vector<int> inputs;
    int input;
    int nvertices;
    int nedges;
  
    cin>>nvertices;
    cin>>nedges;

    
    if(debug) {
      cout<<"Number Verticies:"<< nvertices<<endl;
      cout<<"Number of Edges :"<< nedges <<endl; 
    }
  
    for(int i = 0 ; i < nedges;  i++ ) {
      cin>>input;
      inputs.push_back(input);
      cin>>input;
      inputs.push_back(input);
    }

    graph* g  = new graph(nvertices,adjacency_list);  
    g->nedges = nedges;
    g->nvertices = nvertices;

    for(int i = 0; i < 2*nedges; i += 2) {    
      if(debug)
        cout<<"Adding edge ("<<inputs[i]-1<<","<<inputs[i+1]-1<<")"<<endl;
      
      g->add_mutual_edge(inputs[i]-1,inputs[i+1]-1);      
    }  

    return g;
  }
  
};


void compute_reachability()
{
  graph* g = graph::parse_graph();
  
  int a,b;  
  cin>>a;
  cin>>b;
  a--;
  b--;

  if(a < g->nvertices && b < g->nvertices) {
    if(debug) 
      cout<<"Reachable a->b :"<<a<<"->"<<b<<endl;
    
    cout<<g->reachable(a,b)<<endl;
    
  } else {
    cout<<0<<endl;
  }

}

void compute_components()
{
  graph * g = graph::parse_graph();
  cout<<g->count_components()<<endl;
  delete g;
}


int main(int argc , char* argv[])
{
  
  compute_reachability();
  //compute_components();
}
