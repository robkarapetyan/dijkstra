#include <gtest/gtest.h>
#include "graph.h"

class DijkstraTest : public testing::Test{
public:
  Graph* m_graph = new Graph;
  Graph* m_lgraph = new Graph;

  virtual void SetUp(){
        Node* a = new Node("a");
        Node* b = new Node("b");
        Node* c = new Node("c");
        Node* d = new Node("d");

	    m_graph->add_node(a);
        m_graph->add_node(new Node("a"));
        m_graph->add_node(new Node("b"));
        m_graph->add_node(new Node("e"));
        m_graph->add_node(new Node("f"));
        m_graph->add_node(new Node("c"));
        m_graph->add_node(new Node("d"));

        m_graph->add_edge("a", "b");
        m_graph->add_edge("b", "c");
        m_graph->add_edge("c", "d");
        m_graph->add_edge("b", "f");
        m_graph->add_edge("f", "e");
        m_graph->add_edge("e", "d");

        m_lgraph->add_node(new Node("a"));
        m_lgraph->add_node(new Node("b"));
        m_lgraph->add_node(new Node("c"));
        m_lgraph->add_node(new Node("d"));
        m_lgraph->add_node(new Node("e"));
        m_lgraph->add_node(new Node("f"));
        m_lgraph->add_node(new Node("g"));
        m_lgraph->add_node(new Node("h"));
        m_lgraph->add_node(new Node("i"));
        m_lgraph->add_node(new Node("j"));

        m_lgraph->add_edge("a", "b");
        m_lgraph->add_edge("a", "e");
        m_lgraph->add_edge("b", "c");
        m_lgraph->add_edge("b", "e");
        m_lgraph->add_edge("c", "j");
        m_lgraph->add_edge("j", "d");
        // m_lgraph->add_edge("j", "i");
        m_lgraph->add_edge("j", "e");
        m_lgraph->add_edge("e", "f");
        m_lgraph->add_edge("f", "g");
        m_lgraph->add_edge("f", "h");
        m_lgraph->add_edge("h", "i");
        
  }
  virtual void TearDown(){

  }
};

// Demonstrate some basic assertions->
TEST_F(DijkstraTest, ShortestPathCheck) {
  // Expect two strings to be equal->
  std::string path = m_graph->shortest_path_from_to("a", "d");
  EXPECT_EQ("abcd", path);
  std::cout << "Path from 'a' to 'd' is : '" << path << "'" << std::endl;

  path = m_graph->shortest_path_from_to("d", "a");
  EXPECT_EQ("dcba", path);
  std::cout << "Path from 'd' to 'a' is : '" << path << "'" << std::endl;

  path = m_graph->shortest_path_from_to("a", "e");
  EXPECT_EQ("abfe", path);
  std::cout << "Path from 'a' to 'e' is : '" << path << "'" << std::endl;

  path = m_graph->shortest_path_from_to("e", "a");
  EXPECT_EQ("efba", path);
  std::cout << "Path from 'e' to 'a' is : '" << path << "'" << std::endl;
}

TEST_F(DijkstraTest, ShortestPathCheck2) {
  // Expect two strings to be equal->
  std::string path =  m_lgraph->shortest_path_from_to("c", "h");
  EXPECT_EQ("cbefh", path);
  std::cout << "Path from 'c' to 'h' is : '" << path << "'" << std::endl;


  path = m_graph->shortest_path_from_to("e", "a");
  EXPECT_EQ("efba", path);
  std::cout << "Path from 'e' to 'a' is : '" << path << "'" << std::endl;
}