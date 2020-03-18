#include "test.hpp"

// Test that the path size is zero initially.
TEST_F(RouteModelTest, RouteModelData) {
  EXPECT_EQ(model.path.size(), 0);
  EXPECT_EQ(model.Nodes().size(), model.SNodes().size());
}

// Test that the RouteModel::Node class is defined correctly.
TEST_F(RouteModelTest, RouteModelNode) {
  RouteModel::Node test_node = model.SNodes()[1];
  EXPECT_FLOAT_EQ(test_node.x, 1.2646476);
  EXPECT_FLOAT_EQ(test_node.y, 0.23506972);
  EXPECT_EQ(test_node.parent, nullptr);
  EXPECT_FLOAT_EQ(test_node.h_value, std::numeric_limits<float>::max());
  EXPECT_FLOAT_EQ(test_node.g_value, 0.0);
  EXPECT_FLOAT_EQ(test_node.visited, false);
  EXPECT_EQ(test_node.neighbors.size(), 0);
  RouteModel::Node test_node_2 = RouteModel::Node();
}

// Test the distance function between nodes.
TEST_F(RouteModelTest, NodeDistance) {
  RouteModel::Node test_node = model.SNodes()[1];
  RouteModel::Node test_node_2 = model.SNodes()[4];
  EXPECT_FLOAT_EQ(test_node.distance(test_node_2), 0.10309877);
}
