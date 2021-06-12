#include "graph.h"
#include <iostream>

int main(){
	IGraph* graph = new Graph;
        Node a("t");
        Node b("x");
	graph->add_node(&a);
        graph->add_node(&b);

        graph->shortest_path_from_to("t", "x");
	std::cout << "wtf" << std::endl;
	return 0;
}
