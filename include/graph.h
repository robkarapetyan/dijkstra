#include <map>
#include <string>
#include <string_view>
#include "igraph.h"

class Graph : public IGraph{
public:
	Graph() = default;
	void add_node(Node* node) override;
        void add_edge(const std::string& from,
                      const std::string& to) override;
        void remove_node(const std::string& node_name) override;
        void remove_edge(const std::string& from,
                         const std::string& to) override;
        std::string shortest_path_from_to(const std::string& from,
                                               std::string to) override;
        u_int distance_from_to(const std::string& from,
                                               std::string to) override;
	void erase_data() override;
	~Graph() = default;
		
private:
	std::vector<Node*> nodes = {};
        std::map<Node*, std::pair<u_int, std::string>>
		dijkstra_table = {};	
private:
	void remove_edge(Node* a, Node* b);
        Node* find_node(std::string_view source_node_name);
        void clear_dijkstra_table();
	void fill_dijkstra_table(std::string_view source_node_name);
};

