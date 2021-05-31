#include "igraph.h"
#include <map>
#include <string_view>

class Graph : public IGraph{
public:
	Graph() = default;
	void add_node(Node* node) override;
	void add_edge(std::string_view from, std::string_view to) override;
	
	void remove_node(std::string_view node_name) override;
	void remove_edge(std::string_view from, std::string_view to) override;
	
	std::string_view shortest_path_from_to(std::string_view from, 
					      std::string_view to);

	
	void erase_data() override;
	~Graph() = default;
		
private:
	std::vector<Node*> nodes = {};
	std::map<std::string_view, std::pair<int, std::string_view>> 
		dijkstra_table = {};	
private:
	void remove_edge(Node* a, Node* b);
	Node* find_source_node(std::string_view source_node_name);
	void fill_dijkstra_table(std::string_view source_node_name);
};

