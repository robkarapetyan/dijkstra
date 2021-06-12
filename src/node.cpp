#include "node.h"

Node::Node(std::string_view name) : node_name(name){}

Node::Node(std::string_view name, const std::vector<Node*>& neighbours) : 
	node_name(name), node_neighbours(neighbours){}

void Node::add_neighbour(Node* neighbour_to_add){
	if(neighbour_to_add == nullptr)
		return;

	node_neighbours.emplace_back(neighbour_to_add);
	neighbour_to_add->node_neighbours.emplace_back(this);
}

void Node::remove_neighbour(std::string_view name){
	for(size_t i = 0; i < node_neighbours.size(); ++i){
		if(node_neighbours[i]->node_name == node_name){
			auto it = std::find(node_neighbours[i]->node_neighbours.begin(),
				       	node_neighbours[i]->node_neighbours.end(),
				       	this);
			if(it != node_neighbours[i]->node_neighbours.end()){
				node_neighbours[i]->node_neighbours.erase(it);

			node_neighbours.erase(node_neighbours.begin() + i);
			}
                }
	}
}

void Node::remove_neighbour(Node* node_to_remove){
	auto it = std::find(node_neighbours.begin(), node_neighbours.end(),
		       	node_to_remove);
	if(it != node_neighbours.end()){
		auto it1 = std::find(node_to_remove->node_neighbours.begin(),
				     node_to_remove->node_neighbours.end(),
				     this);
		if(it1 != node_to_remove->node_neighbours.end()){
			node_to_remove->node_neighbours.erase(it1);
		}
		node_neighbours.erase(it);
	}
}

std::string Node::get_name(){
	return node_name;
}

std::vector<Node*> Node::get_neighbours(){
        return node_neighbours;
}
