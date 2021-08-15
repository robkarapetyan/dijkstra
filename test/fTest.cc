#include <gtest/gtest.h>
#include "graph.h"

class DijkstraTest : public testing::Test{
public:
  Graph m_graph;

  virtual void SetUp(){
        Node* a = new Node("a");
        Node* b = new Node("b");
        Node* c = new Node("c");
        Node* d = new Node("d");

	    m_graph.add_node(a);
        m_graph.add_node(b);
        m_graph.add_node(c);
        m_graph.add_node(d);

        m_graph.add_edge("a", "b");
        m_graph.add_edge("a", "c");
        m_graph.add_edge("b", "d");
        m_graph.add_edge("c", "b");
  }
  virtual void TearDown(){

  }
};

// Demonstrate some basic assertions.
TEST_F(DijkstraTest, ShortestPathCheck) {
  // Expect two strings to be equal.
  EXPECT_EQ("abd", m_graph.shortest_path_from_to("a", "d"));
}