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


  node_color color;
  vector<node*> neighbours;
  node_visited visited;


public:
  int id;
  void* data;
  
  int pre_visit_order = -1;
  int post_visit_order = -1;

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
    if(debug) cout<<"done:"<< id<<endl;
  }

  static bool sortby_postvisit(const node* n1 , const node* n2){
    return n1->post_visit_order > n2->post_visit_order;
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
  bool directed = false;

public:
  graph(int n,graph_store st,bool directed): size(n), type(st),directed(directed) {
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

  void add_edge(int a, int b) {
    nodes[a]->neighbours.push_back(nodes[b]);
    if(!directed) {
      nodes[b]->neighbours.push_back(nodes[a]);
    }
  }

  void mark_unvisited() {
    for(node*  n : nodes){
      n->mark_unvisited();
      n->pre_visit_order = -1;
      n->post_visit_order -1;
    }
  }

  void dfs_visit(node* a,int* order) {
    a->mark_visting();
    a->pre_visit_order = *order;
    for(node* n : a->neighbours )
      if(n->unvisitedp()) {
        (*order)++;
        dfs_visit(n,order);
      }
    a->mark_visited();
    (*order)++;
    a->post_visit_order = *order;
  }

  int reachable(int a, int b) {
    this->mark_unvisited();
    int order = 0;
    this->dfs_visit(nodes[a],&order);
    return !(nodes[b]->unvisitedp());
  }

  int count_components() {
    this->mark_unvisited();
    int count = 0;
    int order = 0;
    for(node* node : nodes) {
      if(node->unvisitedp()) {
          count++;
          dfs_visit(node,&order);
      }
    }
    return count;
  }

  vector<node*> topological_order()
  {
    this->mark_unvisited();
    int count = 0;
    int order =0;
    for(node* node: nodes) {
      if(node->unvisitedp()) {
        dfs_visit(node,&order);
      }
    }

    vector<node*>* retval = new vector<node*>();
    *retval = nodes;
    sort(retval->begin(),retval->end(),node::sortby_postvisit);
    return *retval;
  }

  static graph* parse_graph(bool directed) {
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

    graph* g  = new graph(nvertices,adjacency_list,directed);
    g->nedges = nedges;
    g->nvertices = nvertices;

    for(int i = 0; i < 2*nedges; i += 2) {
      if(debug)
        cout<<"Adding edge ("<<inputs[i]-1<<","<<inputs[i+1]-1<<")"<<endl;

      g->add_edge(inputs[i]-1,inputs[i+1]-1);
    }

    return g;
  }
};


void compute_reachability()
{
  graph* g = graph::parse_graph(false);

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
  graph * g = graph::parse_graph(false);
  cout<<g->count_components()<<endl;
  delete g;
}

void topological_sort(){
  graph *g = graph::parse_graph(true);
  vector<node*> nodes =  g->topological_order();
  for (node* n : nodes) {
    cout<<n->id+1;
    
    if(debug)
      cout<<":"<< (n->pre_visit_order)<<"/"<<(n->post_visit_order);
    
    cout<< " ";
  }
  cout<<endl;
}

int main(int argc , char* argv[])
{

  //compute_reachability();
  //compute_components();
  topological_sort();
}
