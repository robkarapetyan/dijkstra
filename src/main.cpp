#include "graph.h"
#include <iostream>

int main(){
	IGraph* graph = new Graph;
        Node a("a");
        Node b("b");
        Node c("c");
        Node d("d");

	graph->add_node(&a);
        graph->add_node(&b);
        graph->add_node(&c);
        graph->add_node(&d);

        graph->add_edge("a", "b");
        graph->add_edge("a", "c");
        graph->add_edge("b", "d");
        graph->add_edge("c", "d");

	std::cout << "distance from a to d : "
                 << graph->distance_from_to("a", "d") << std::endl;
        std::cout <<  "path from a to d : "
                << graph->shortest_path_from_to("a", "d") << std::endl;

	return 0;
}
