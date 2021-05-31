#pragma once
#include <algorithm>
#include <string_view>
#include <vector>
#include <string>

struct Node{
public:
	Node(std::string_view name);
	Node(std::string_view name, const std::vector<Node*>& neighbours);
	
	std::string_view get_name();	
	void add_neighbour(Node* neighbour_to_add);

	void remove_neighbour(std::string_view name);
	void remove_neighbour(Node* node_to_remove);
private:
	std::string node_name;
	std::vector<Node*> node_neighbours = {};
	friend class Graph;	
};
