#include "parser.h"

void Parser::parse(std::istream &input, const InputFormat &format)
{
    // expected input format
    // 1. graph nodes (a, b, c, d, e, f)
    // 2. graph edges (a-b, a-c, d-e, d-f, b-f)
    // 3. nodes to find shortest path between (a, d)
    std::string str;
    std::getline(input, str);
    int tokenPos = 0;
    std::string token;

    switch (format)
    {
    case InputFormat::nodes:
    {
        while ((tokenPos = str.find(",")) != std::string::npos)
        {
            token = str.substr(0, tokenPos);
            m_graph->add_node(new Node(token));
            str.erase(0, tokenPos + 2);
        }
        m_graph->add_node(new Node(str));
        break;
    }
    case InputFormat::edges:
    {
        while ((tokenPos = str.find(",")) != std::string::npos)
        {
            token = str.substr(0, tokenPos);
            int abBorder = token.find("-");
            std::string tokenA = token.substr(0, abBorder);
            std::string tokenB = token.substr(abBorder + 1, token.npos);
            m_graph->add_edge(tokenA, tokenB);
            str.erase(0, tokenPos + 2);
        }
        std::string tokenA = str.substr(0, str.find("-"));
        std::string tokenB = str.substr(str.find("-") + 1, str.npos);
        m_graph->add_edge(tokenA, tokenB);
        break;
    }
    case InputFormat::pathBetween:
    {
        while (str != "-q")
        {
            while ((tokenPos = str.find(",")) != std::string::npos)
            {
                token = str.substr(0, tokenPos);
                str.erase(0, tokenPos + 2);
                std::string path = m_graph->shortest_path_from_to(token, str);
                int distance = m_graph->distance_from_to(token, str);
                std::cout << "Shortest path from '" << token << "' to '" << str <<"' is : " << 
                path << ". With distance of " << 
                distance << std::endl;
            }
            str.clear();
            std::getline(std::cin, str);
        }
        break;
    }
    default:
        break;
    }
}