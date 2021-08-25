#include <iostream>
#include "graph.h"
#include "parser.h"

int main(){
        Parser parser;
        std::cout << " Expected input format " << std::endl;
        std::cout << " 1. graph nodes (a, b, c, d, e, f)" << std::endl; 
        std::cout << " 2. graph edges (a-b, a-c, d-e, d-f, b-f)" << std::endl;
        std::cout << " 3. nodes to find shortest path between (a, d)" << std::endl;
        std::cout << " -q to exit." << std::endl;

        parser.parse(std::cin, InputFormat::nodes);
        parser.parse(std::cin, InputFormat::edges);
        parser.parse(std::cin, InputFormat::pathBetween);
	return 0;
}
