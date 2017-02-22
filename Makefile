FLAGS:=-pipe -O2 -std=c++0x

all:scc rechability components topological acyclic


rechability: graph.cpp
	g++  $(FLAGS) graph.cpp -DRECHABILITY -lm -o bin/reachability

components: graph.cpp
	g++  $(FLAGS) graph.cpp -DCOMPONENTS -lm -o bin/components

topological: graph.cpp
	g++  $(FLAGS) graph.cpp -DTOPOLOGICAL -lm -o bin/topological

acyclic: graph.cpp
	g++  $(FLAGS) graph.cpp -DACYCLIC -lm -o bin/acyclic

scc: graph.cpp
	g++  $(FLAGS) graph.cpp -DSCC -lm -o bin/scc	