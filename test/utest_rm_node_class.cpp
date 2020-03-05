#include "test.hpp"

// Test that the RouteModel::Node class is defined correctly.
TEST_F(RouteModelTest, RouteModelNode) {
    RouteModel* p_model = &model;
    RouteModel::Node test_node = RouteModel::Node(1, p_model, model.Nodes()[1]);
    EXPECT_FLOAT_EQ(test_node.x, 1.2646476);
    EXPECT_FLOAT_EQ(test_node.y, 0.23506972);
    EXPECT_EQ(test_node.parent, nullptr);
    EXPECT_FLOAT_EQ(test_node.h_value, std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(test_node.g_value, 0.0);
    EXPECT_FLOAT_EQ(test_node.visited, false);
    EXPECT_EQ(test_node.neighbors.size(), 0);
    RouteModel::Node test_node_2 = RouteModel::Node();
}
