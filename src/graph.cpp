#include <iostream>
#include <set>
#include "graph.h"

void Graph::add_node(Node *node)
{
	if (nullptr == node)
	{
		return;
	}
	if (nodes.empty())
	{
		nodes.emplace_back(node);
		return;
	}
	if (find_node(node->get_name()) == nullptr)
	{
		nodes.emplace_back(node);
	}
}

void Graph::add_edge(const std::string &from,
					 const std::string &to)
{
	Node *a = find_node(from);
	Node *b = find_node(to);

	if (a and b){
		a->add_neighbour(b);
	}
}

void Graph::remove_node(const std::string &node_to_remove_name)
{
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		if (nodes[i]->get_name() == node_to_remove_name)
		{
			for (auto j : nodes[i]->get_neighbours())
			{
				nodes[i]->remove_neighbour(j);
			}
			delete (nodes[i]);
			nodes.erase(nodes.begin() + i);
		}
	}
}

void Graph::remove_edge(const std::string &from,
						const std::string &to)
{
	Node *a = nullptr;
	Node *b = nullptr;
	for (auto i : nodes)
	{
		if (i->get_name() == from)
		{
			a = i;
		}
		else if (i->get_name() == to)
		{
			b = i;
		}
	}
	a->remove_neighbour(b);
}

void Graph::erase_data()
{
	for (auto p : nodes)
	{
		delete p;
	}
	nodes.clear();
}

std::string Graph::shortest_path_from_to(const std::string &from,
										 const std::string &to)
{
	try
	{
		if (find_node(from) == nullptr or find_node(to) == nullptr)
		{
			throw std::invalid_argument("Node not found");
		}
	}
	catch (std::invalid_argument ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::string to_tmp = to;
	fill_dijkstra_table(from);
	std::string ret_str = "";
	ret_str.insert(0, to_tmp);
	while (to_tmp != from)
	{
		ret_str.insert(0, dijkstra_table[find_node(to_tmp)].second);
		to_tmp = dijkstra_table[find_node(to_tmp)].second;
	}
	print_dijkstra_table();
	return ret_str;
}

uint32_t Graph::distance_from_to(const std::string &from,
								 const std::string &to)
{
	try
	{
		if (find_node(from) == nullptr or find_node(to) == nullptr)
		{
			throw std::invalid_argument("Node not found");
		}
	}
	catch (std::invalid_argument ex)
	{
		std::cout << ex.what() << std::endl;
	}
	fill_dijkstra_table(from);
	return dijkstra_table[find_node(to)].first;
}

// Private

void Graph::remove_edge(Node *a, Node *b)
{
	if (a != nullptr or b != nullptr){
		return;
	}
	a->remove_neighbour(b);
}

Node *Graph::find_node(std::string_view source_node_name)
{
	for (Node *a : nodes)
	{
		if (a->get_name() == source_node_name)
		{
			return a;
		}
	}
	return nullptr;
}

void Graph::fill_dijkstra_table(std::string_view source_node_name){
	clear_dijkstra_table();

	Node *current_node = find_node(source_node_name);
	Node *next_node = nullptr;

	if (current_node == nullptr) {
		return;
	}
	std::set<Node*> visited;
	std::multimap<int, Node*> priority_map; // A multimap representing nodes with their distances from root as keys

	visited.insert(current_node);
	dijkstra_table[current_node] = { 0, "root" };
	std::vector<Node*> neighbours = current_node->get_neighbours();
	for (int i = 0; !neighbours.empty(), i < neighbours.size(); ++i) {
		dijkstra_table[neighbours[i]] = { 1, current_node->get_name() };
		priority_map.insert({ 1, neighbours[i] });
	}

	while (!priority_map.empty()) {
		if (visited.find(priority_map.begin()->second) == visited.end()) {
			current_node = priority_map.begin()->second;
			neighbours = current_node->get_neighbours();
			for (int i = 0; !neighbours.empty(), i < neighbours.size(); ++i)
			{
				auto it = dijkstra_table.find(neighbours[i]);
				if (it == dijkstra_table.end() or it != dijkstra_table.end() 
				and it->second.first > dijkstra_table[current_node].first + 1)
				{
					dijkstra_table[neighbours[i]] = {dijkstra_table[current_node].first + 1, current_node->get_name()};
				}
				priority_map.insert({dijkstra_table[current_node].first + 1, neighbours[i]});
			}
			visited.insert(current_node);
		}
		priority_map.erase(priority_map.begin());
	}
}

void Graph::print_dijkstra_table()
{
	std::cout << "node	distance	previous" << std::endl;
	for (auto i = dijkstra_table.begin(); i != dijkstra_table.end(); ++i)
	{
		std::cout << i->first->get_name() << "	" << i->second.first << "		" << i->second.second << std::endl;
	}
}

void Graph::clear_dijkstra_table()
{
	dijkstra_table.clear();
}

Graph::~Graph()
{
	erase_data();
}