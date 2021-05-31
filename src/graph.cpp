#include "graph.h"
#include <iostream>
#include <string>
#include <set>

void Graph::add_node(Node* node){ 
	if(node != nullptr)
		nodes.emplace_back(node);
}

void Graph::add_edge(std::string_view from, std::string_view to){
	Node* a = nullptr;
	Node* b = nullptr;

	for(auto i : nodes){
		if(i->node_name == from){
			a = i;
		}else if(i->node_name == to){
			b = i;
		}
	}
	a->add_neighbour(b);
}

void Graph::remove_node(std::string_view node_to_remove_name){
	for(size_t i = 0; i < nodes.size(); ++i){
		if(nodes[i]->node_name == node_to_remove_name){
			for(auto j : nodes[i]->node_neighbours){
				nodes[i]->remove_neighbour(j);
			}
			delete(nodes[i]);
			nodes.erase(nodes.begin() + i);
		}
	}
}

void Graph::remove_edge(Node* a, Node* b){
	if(a != nullptr || b != nullptr)
		return;
	a->remove_neighbour(b);
}

void Graph::remove_edge(std::string_view from, std::string_view to){
	Node* a = nullptr;
	Node* b = nullptr;
	for(auto i : nodes){
		if(i->node_name == from){
			a = i;
		}else if(i->node_name == to){
			b = i;
		}
	}
	a->remove_neighbour(b);	
}

void Graph::erase_data(){
	for(auto p : nodes){
		delete p;
	}
	nodes.clear();
}
/*
Node* Graph::find_node_by_name(std::string_view name){
	Node* a = nullptr;
	for(auto i : 
}*/

std::string_view Graph::shortest_path_from_to(std::string_view from,
					      std::string_view to){
	//
	fill_dijkstra_table(from);
	//
	std::string str = "";
	while (to != from){
		str.insert(0, {dijkstra_table[to].second.data(),
			 	dijkstra_table[to].second.size()});
		to = dijkstra_table[to].second;
	
	}
	str.insert(0, from);
	return str;
}

Node* Graph::find_source_node(std::string_view source_node_name){
	//
	for (Node* a : nodes){
	//
		if (a->get_name() == source_node_name){
		return a;
		}
	}
	return nullptr;
}
	
void Graph::fill_dijkstra_table(std::string_view source_node_name){
	dijkstra_table.clear();

	Node* current_node = find_source_node(source_node_name);
	Node* next_node = nullptr;

	if (current_node == nullptr)
		return;
	std::set<std::string_view> visited_vertices = {};
	dijkstra_table.emplace(current_node->get_name(), std::pair<int,
		       				std::string_view>{ 0, ""});
	//visited_vertices.emplace(current_node->get_name());

	while (visited_vertices.size() <= nodes.size()){
		//auto it = std::find(

		for(const auto& i : current_node->node_neighbours){
			auto it = std::find( visited_vertices.begin(),
				       	visited_vertices.end(),
				       	i->get_name());
			if (it == visited_vertices.end()){
				int distance = dijkstra_table[current_node->get_name()]
					.first + 1;
				auto itt = std::find(dijkstra_table.begin(),
						dijkstra_table.end(), i->get_name());
				if(itt != dijkstra_table.end()){
			       		if (itt->second.first > distance){
						dijkstra_table.emplace(
							i->get_name(),
						       std::pair<int, std::string_view>	
							{ distance, current_node
							->get_name()});	
					}
				} else {
					dijkstra_table.emplace(i->get_name(),
						std::pair<int, std::string_view>
					       	{ distance, current_node->get_name()} );
				}
				next_node = i;
			}
		}
		visited_vertices.emplace(current_node->get_name());
		current_node = next_node;
	}

}

