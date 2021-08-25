#include <string_view>
#include <iostream>
#include <memory>
#include "graph.h"

enum class InputFormat{ nodes, edges, pathBetween};

class Parser
{
public:
    void parse(std::istream& input, const InputFormat& format);
private:
	std::unique_ptr<IGraph> m_graph = std::make_unique<Graph>();
};