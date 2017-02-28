<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1. Algorithms on Graphs</a>
<ul>
<li><a href="#sec-1-1">1.1. Week-1</a>
<ul>
<li><a href="#sec-1-1-1">1.1.1. Connectivity</a></li>
<li><a href="#sec-1-1-2">1.1.2. Pre and Post Orderings</a></li>
</ul>
</li>
<li><a href="#sec-1-2">1.2. Week-2</a>
<ul>
<li><a href="#sec-1-2-1">1.2.1. Directed Graphs</a></li>
<li><a href="#sec-1-2-2">1.2.2. Topological Sorting</a></li>
<li><a href="#sec-1-2-3">1.2.3. Strongly Connected Components</a></li>
</ul>
</li>
<li><a href="#sec-1-3">1.3. Week-3</a>
<ul>
<li><a href="#sec-1-3-1">1.3.1. Breadth First Search</a></li>
<li><a href="#sec-1-3-2">1.3.2. Proof of Correctness</a></li>
<li><a href="#sec-1-3-3">1.3.3. Shortest Part Trees</a></li>
<li><a href="#sec-1-3-4">1.3.4. Reconstructing Shortest Paths</a></li>
</ul>
</li>
<li><a href="#sec-1-4">1.4. Week-4</a>
<ul>
<li><a href="#sec-1-4-1">1.4.1. Shortest Path</a></li>
<li><a href="#sec-1-4-2">1.4.2. Dijsktra's Algorithm</a></li>
<li><a href="#sec-1-4-3">1.4.3. Bellman Ford's algorithm</a></li>
<li><a href="#sec-1-4-4">1.4.4. Negative Cycles</a></li>
</ul>
</li>
<li><a href="#sec-1-5">1.5. Week-5</a>
<ul>
<li><a href="#sec-1-5-1">1.5.1. Minimum Spanning Tree mst</a></li>
<li><a href="#sec-1-5-2">1.5.2. Greedy Algorithms</a></li>
<li><a href="#sec-1-5-3">1.5.3. Cut Property</a></li>
<li><a href="#sec-1-5-4">1.5.4. Kruskal's Algorithm</a></li>
<li><a href="#sec-1-5-5">1.5.5. Prim's Algorithm</a></li>
</ul>
</li>
<li><a href="#sec-1-6">1.6. Week-6</a>
<ul>
<li><a href="#sec-1-6-1">1.6.1. Bidirectional Dijsktra</a></li>
<li><a href="#sec-1-6-2">1.6.2. A* Algorithm</a></li>
<li><a href="#sec-1-6-3">1.6.3. Contraction Algorithms</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>

# Algorithms on Graphs<a id="sec-1" name="sec-1"></a>

## Week-1<a id="sec-1-1" name="sec-1-1"></a>

### Connectivity<a id="sec-1-1-1" name="sec-1-1-1"></a>

### Pre and Post Orderings<a id="sec-1-1-2" name="sec-1-1-2"></a>

## Week-2<a id="sec-1-2" name="sec-1-2"></a>

### Directed Graphs<a id="sec-1-2-1" name="sec-1-2-1"></a>

### Topological Sorting<a id="sec-1-2-2" name="sec-1-2-2"></a>

### Strongly Connected Components<a id="sec-1-2-3" name="sec-1-2-3"></a>

## Week-3<a id="sec-1-3" name="sec-1-3"></a>

### Breadth First Search<a id="sec-1-3-1" name="sec-1-3-1"></a>

### Proof of Correctness<a id="sec-1-3-2" name="sec-1-3-2"></a>

### Shortest Part Trees<a id="sec-1-3-3" name="sec-1-3-3"></a>

### Reconstructing Shortest Paths<a id="sec-1-3-4" name="sec-1-3-4"></a>

## Week-4<a id="sec-1-4" name="sec-1-4"></a>

### Shortest Path<a id="sec-1-4-1" name="sec-1-4-1"></a>

### Dijsktra's Algorithm<a id="sec-1-4-2" name="sec-1-4-2"></a>

### Bellman Ford's algorithm<a id="sec-1-4-3" name="sec-1-4-3"></a>

### Negative Cycles<a id="sec-1-4-4" name="sec-1-4-4"></a>

## Week-5<a id="sec-1-5" name="sec-1-5"></a>

### Minimum Spanning Tree <a id="mst" name="mst">mst</a><a id="sec-1-5-1" name="sec-1-5-1"></a>

A 1.5.1.1 which spans every vertex \(V\) in graph \(G\). Subset of edges \(E
\in G(V,E)\) such that \(\sum w(e) \forall e \in E\) is minimum.

1.  <a id="tree" name="tree"></a> Tree

    A tree is an undirected graph which is connected and acyclic.
    
    1.  Tree Properties
    
        1.  A tree with \(n\) nodes will have \(n-1\) endges.
        2.  A connected,undirected graph \(G(V,E)\) with $|V| -1 $ edges is by definition a tree.
        3.  An undirected graph with a **unique path** between any two pairs of vertices is by definition a tree.

### Greedy Algorithms<a id="sec-1-5-2" name="sec-1-5-2"></a>

1.  Kruskal's Algorithm Summary

    1.  Repeatedly add the next lightest edge of G(V,E) such that adding the edge does not produce a cycle
    2.  Terminate when no more edges can be added to the graph \(G\)

2.  Prim's Algorithms Summary

    1.  Repeatedly add the new vertex to the **current tree** by the next light edge.
    2.  Terminate when all vertices have been added  to the **current tree**

### Cut Property<a id="sec-1-5-3" name="sec-1-5-3"></a>

Let \(X \in E\) be a part of a **minimum spaning tree** of \(G(V,E)\) such that \(S \in V\) and there is
no edge between \(S\) and \(V-S\). and \(e \in E\) be the lightest edge between \(S\) and \(V-S\) then 
\(e\) this lightest edge is part of the **minimum spanning tree**

1.  Proof:

    1.  Consider disjoint \(S\) and \(V-S\) set of vertices.
    2.  Let \(e\) be the minum vertex between all vertices between \(S\) and \(V-S\) such that \(e\) is not in the MST.
    3.  Let \(e'\) be an edge in the minimum spanning tree containing \(S\) and \(V-S\)
    4.  Since MST is a tree adding an edge  \(e\) will create a cycle containing the edges \(e\) and \(e'\)
    5.  Deleting any edge in the cycle will leave the graph connected.
    6.  Since  \(w(e) < w(e')\)  removing edge \(e'\) and adding keeping the edge \(e\) will produce a tree 
        with weight smaller than MST.
    7.  Thus by contradiction \(e\) must be in the MST.

### Kruskal's Algorithm<a id="sec-1-5-4" name="sec-1-5-4"></a>

1.  Repeatedly add to \(X\) the next lightest edge that does not create
    a cycle.
2.  \(X\) starts off as a forest of trees

1.  Implementation Details

    1.  Use disjoint sets datastructure.
    2.  Every vertex starts off in disjoint set
    3.  Each set is a vertex of connected components
    4.  If \(u\) and \(v\) are in disjoint sets adding edge \((u,v)\) will not create a cycle.
    
        1. for all v \in V
             MakeSet(v)
        2. X <- {}
        3. sort edges by weight
        4. for all {u,v} \in E
            if Set(u) != Set(v):
              X <- X + (u,v) 
              Union(u,v)
        5. return X {tree}

2.  Runtime Information

    O(|E|log(V))
    
    1.  Sorting Edges
    
        \(O(|E| log(|E|)) => O(|E| log(V))\)
    
    2.  Processing Edges
    
        2|E|.T(Find) | + |V| T(Union) 
        O(|E| log(V))

### Prim's Algorithm<a id="sec-1-5-5" name="sec-1-5-5"></a>

Very similar to dijkstra's algorithm

1.  Grow the subtree one edge at a time.
2.  Add lightest edge between tree and remaining vertices => **prevents cycles**
3.  Done when all vertices are added

1.  Prim's Algorithm Implementation

        for u in vertices(G):
           cost[u] = inf
        start = random(u)
        cost[u] = 0
        queue = make_priority_queue(zip(V,cost));
        
        while not queue.empty():
          (cost,v)  = queue.min();
          for all (v,z) in edges(v):
             if queue.contains(v) and cost[z] > w(v,z):
                  cost[z] = w(v,z), parent[z] = v
                  queue.change_priority(z,cost[z])

2.  Prim's Running Time

    O(|V|.T(min)) + |E|. T(change<sub>priority</sub>)
    
    Using heap T(min) 

## Week-6<a id="sec-1-6" name="sec-1-6"></a>

### Bidirectional Dijsktra<a id="sec-1-6-1" name="sec-1-6-1"></a>

### A\* Algorithm<a id="sec-1-6-2" name="sec-1-6-2"></a>

### Contraction Algorithms<a id="sec-1-6-3" name="sec-1-6-3"></a>