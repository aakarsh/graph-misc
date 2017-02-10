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
  node_visited visit_state;
public:
  int id;
  void* data;
  int pre_visit_order = -1;
  int post_visit_order = -1;

  node(int id, void* ptr): node(id,ptr,white){}
  node(int id, void* ptr, node_color c): id(id), data(ptr),color(c),visit_state(unvisited){}


  friend class graph;

  void mark_visting()   {
    visit_state = visiting;
    if(debug)
      cout<<"visiting:"<< id <<endl;
  }

  void mark_unvisited() {
    visit_state = unvisited;
  }

  void mark_visited()   {
    visit_state = visited;
    if(debug) cout<<"done:"<< id<<":"<<visit_state<<endl;
  }

  static bool sortby_postvisit(const node* n1 , const node* n2){
    return n1->post_visit_order > n2->post_visit_order;
  }

  bool unvisitedp() { return visit_state == unvisited; }
  bool visitingp()  { return visit_state == visiting; }

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
  vector<vector<node*>*> node_adjacency;
  
public:
  graph(int n,graph_store st,bool directed): size(n), type(st),directed(directed) {
    switch(st){
    case adjacency_list:
      for(int i = 0 ; i < n ; i++){
        nodes.push_back(new node(i,NULL, white));
      }
      for(int i = 0; i < n; i++) {
        node_adjacency.push_back(new vector<node*>());
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
    node_adjacency[a]->push_back(nodes[b]);
    
    if(!directed) {
      node_adjacency[b]->push_back(nodes[a]);
    }
  }

  void mark_unvisited() {
    for(node*  n : nodes){
      n->mark_unvisited();
      n->pre_visit_order = -1;
      n->post_visit_order -1;
    }
  }

  /*
  graph* reverse_graph(){
    graph* g = new graph(nvertices,adjacency_list,directed);
    for(node* n : nodes) {
      for(node* nb : n->neighbours) {
        
      }
    }
  }
  */



  class dfs_visitor {
  private:
    int backedges = 0;
    int order = 0;
    int components = 0;
  public:
    graph* g;


    dfs_visitor(graph* g) : g(g){}

    dfs_visitor* visit_graph(){
      g->mark_unvisited();
      for(node*  n : g->nodes){
        if(n->unvisitedp()) {
          visit(n);
          components++;
        }
      }
      return this;
    }

    dfs_visitor* visit(node* cur) {
      pre_visit(cur);
      for(node* n : *(g->node_adjacency[cur->id])) { 
        if(debug)
          cout<<"Examine :"<<cur->id<<"->"<<n->id<<" "<<n->visit_state<<endl;

        if(n->unvisitedp()) {
          order++;
          visit(n);
        } else if(n->visitingp()) {// back edge
          if(debug)
            cout<<"backedge "<<cur->id<<"->"<<n->id<<endl;
          backedges++;
        }
      }
      post_visit(cur);
      return this;
    }

    bool cyclep() {
      return backedges > 0;
    }

    int num_components() { return components;  }
    int num_backedges() {  return backedges; }

    void post_visit(node* cur){
      cur->mark_visited();
      order++;
      cur->post_visit_order = order;
    }

    void pre_visit(node* cur) {
      cur->mark_visting();
      cur->pre_visit_order = order;
    };

  };

  int reachable(int a, int b) {
    this->mark_unvisited();
    dfs_visitor visitor(this);
    visitor.visit(nodes[a]);
    return !(nodes[b]->unvisitedp());
  }

  int count_components() {
    dfs_visitor visitor(this);
    return (visitor.visit_graph())->num_components();
  }

  int check_acyclic() {
    dfs_visitor visitor(this);
    return (visitor.visit_graph())->cyclep();
  }

  vector<node*> topological_order()
  {
    dfs_visitor visitor(this);
    visitor.visit_graph();
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

void compute_acyclic(){
  graph *g = graph::parse_graph(true);
  if(g->check_acyclic()){
    cout<<1<<endl;
  } else{
    cout <<0<<endl;
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
  #ifdef RECHABILITY
  compute_reachability();
  #endif

  #ifdef COMPONENTS
  compute_components();
  #endif

  #ifdef TOPOLOGICAL
  topological_sort();
  #endif

  #ifdef ACYCLIC
  compute_acyclic();
  #endif
}
