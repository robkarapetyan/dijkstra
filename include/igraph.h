#pragma once
#include "node.h"

class IGraph{
public:
	IGraph() = default;
	
	virtual void add_node(Node* node) = 0;
	virtual void add_edge(std::string_view from, std::string_view to) = 0;
	
	virtual void remove_node(std::string_view node_name) = 0;
	virtual void remove_edge(std::string_view from, std::string_view to) = 0;
	virtual void erase_data() = 0;
	virtual ~IGraph(){}
};
