#include "graph.h"
#include <iostream>

int main(){
	IGraph* graph = new Graph;
	Node a("ttx");
	graph->add_node(&a);

	std::cout << "wtf" << std::endl;
	return 0;
}
