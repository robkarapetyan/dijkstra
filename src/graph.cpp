#include <iostream>
#include <set>
#include <stack>
#include <string_view>
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

	if (a and b)
		a->add_neighbour(b);
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
											  std::string to)
{
	if (find_node(from) == nullptr or find_node(to) == nullptr){
		return "check the node names";
	}
	fill_dijkstra_table(from);
	std::string str = "";
	str.insert(0, to);
	while (to != from)
	{
		str.insert(0, dijkstra_table[find_node(to)].second);
		to = dijkstra_table[find_node(to)].second;
	}
	return str;
}

u_int Graph::distance_from_to(const std::string &from,
							  std::string to)
{
	if (find_node(from) != nullptr and find_node(to) != nullptr)
	{
		fill_dijkstra_table(from);
		return dijkstra_table[find_node(to)].first + 1;
	}
}

// Private

void Graph::remove_edge(Node *a, Node *b)
{
	if (a != nullptr || b != nullptr)
		return;
	a->remove_neighbour(b);
}

Node *Graph::find_node(std::string_view source_node_name)
{
	for (Node *&a : nodes)
	{
		if (a->get_name() == source_node_name)
		{
			return a;
		}
	}
	return nullptr;
}

void Graph::fill_dijkstra_table(std::string_view source_node_name)
{
	clear_dijkstra_table();

	Node *current_node = find_node(source_node_name);
	Node *next_node = nullptr;

	if (current_node == nullptr)
		return;

	std::set<Node *> visited_vertices = {};
	std::stack<Node *> node_stack = {};

	dijkstra_table.emplace(current_node, std::pair<int,
												   std::string>{0, ""});
	node_stack.push(current_node);

	while (node_stack.empty() == false)
	{
		for (auto i : current_node->node_neighbours)
		{
			auto it = std::find(visited_vertices.begin(),
								visited_vertices.end(),
								i);
			if (it == visited_vertices.end())
			{
				u_int distance_of_i_node = dijkstra_table[i].first;
				u_int distance_of_curr_plus_one = dijkstra_table[current_node].first + 1;

				if (distance_of_i_node > distance_of_curr_plus_one)
				{
					dijkstra_table[i] = std::pair<u_int, std::string>(
						distance_of_curr_plus_one, current_node->get_name());
				}
				node_stack.push(i);
				next_node = i;
			}
		}
		visited_vertices.emplace(current_node);
		if (current_node == next_node)
		{
			if (current_node == node_stack.top())
			{
				while (next_node == node_stack.top())
				{
					node_stack.pop();
				}
			}
		}
		if (node_stack.empty() == false)
		{
			next_node = node_stack.top();
			node_stack.pop();
		}

		current_node = next_node;
	}
}

void Graph::clear_dijkstra_table()
{

	dijkstra_table.clear();
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		dijkstra_table.emplace(*it, std::pair<u_int, std::string>(
										-1, ""));
	}
}