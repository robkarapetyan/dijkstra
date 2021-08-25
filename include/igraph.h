#pragma once
#include "node.h"

class IGraph
{
public:
        IGraph() = default;

        virtual void add_node(Node *node) = 0;
        virtual void add_edge(const std::string &from,
                              const std::string &to) = 0;

        virtual void remove_node(const std::string &node_name) = 0;
        virtual void remove_edge(const std::string &from,
                                 const std::string &to) = 0;
        virtual void erase_data() = 0;
        virtual std::string shortest_path_from_to( //constness ??
            const std::string &from,
            const std::string &to) = 0;
        virtual uint32_t distance_from_to(const std::string &from, //constness ??
                                       const std::string &to) = 0;
        virtual ~IGraph() {}
};
