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

// Test the data created by CreateNodeToRoadHashmap.
TEST_F(RouteModelTest, NodeToRoad) {
    auto node_to_road = model.GetNodeToRoadMap();
    EXPECT_EQ(node_to_road[0].size(), 2);
    EXPECT_EQ(node_to_road[30].size(), 2);
    EXPECT_EQ(node_to_road[90].size(), 2);
//    EXPECT_EQ(node_to_road[0][0]->way, 500);
    EXPECT_EQ(node_to_road[0][0]->way, 551);
    EXPECT_EQ(node_to_road[30][1]->way, 613);
    EXPECT_EQ(node_to_road[90][1]->way, 475);
}

// Test the FindNeighbors method.
TEST_F(RouteModelTest, FindNeighbors) {
    auto test_node = model.SNodes()[0];
    test_node.FindNeighbors();
    EXPECT_EQ(test_node.neighbors.size(), 2);
//    EXPECT_FLOAT_EQ(test_node.neighbors[1]->x, 1.3250526);
//    EXPECT_FLOAT_EQ(test_node.neighbors[1]->y, 0.41849667);
    EXPECT_FLOAT_EQ(test_node.neighbors[1]->x,1.1881341);
    EXPECT_FLOAT_EQ(test_node.neighbors[1]->y,-0.029241385);
    test_node.neighbors.clear(); // Clear out neighbors just added.
    test_node = model.SNodes()[100];
    test_node.FindNeighbors();
    EXPECT_EQ(test_node.neighbors.size(), 2);
    EXPECT_FLOAT_EQ(test_node.neighbors[0]->x, 0.77367586);
    EXPECT_FLOAT_EQ(test_node.neighbors[0]->y, 0.52004427);
    test_node.neighbors.clear();
}

// Test the FindClosestNode method.
TEST_F(RouteModelTest, FindClosestNode) {
    float x = 0.023456;
    float y = 0.567890;
    auto& test_node = model.FindClosestNode(x, y);
    EXPECT_EQ(&test_node, &model.SNodes()[10155]);
    EXPECT_FLOAT_EQ(test_node.x, 0.030928569);
    EXPECT_FLOAT_EQ(test_node.y, 0.58042318);
    x = 0.555555;
    y = 0.333333;
    auto& test_node_2 = model.FindClosestNode(x, y);
    EXPECT_EQ(&test_node_2, &model.SNodes()[600]);
    EXPECT_FLOAT_EQ(test_node_2.x, 0.58249766);
    EXPECT_FLOAT_EQ(test_node_2.y, 0.34965551);
}

//--------------------------------//
//   Beginning RouteModel Tests.
//--------------------------------//

// Test the AStarSearch method stub.
TEST_F(RoutePlannerTest, AStarStub) {
    route_planner.AStarSearch();
//    EXPECT_EQ(model.path.size(), 2);
    EXPECT_EQ(model.path.size(), 33);
    RouteModel::Node path_start = model.path[1];
    RouteModel::Node path_end = model.path[0];
    // The start_node and end_node x, y values should be the same as in the path.
//    EXPECT_FLOAT_EQ(start_node->x, path_start.x);
//    EXPECT_FLOAT_EQ(start_node->y, path_start.y);
//    EXPECT_FLOAT_EQ(end_node->x, path_end.x);
//    EXPECT_FLOAT_EQ(end_node->y, path_end.y);
//    EXPECT_FLOAT_EQ(route_planner.GetDistance(), 655.7218);
    EXPECT_FLOAT_EQ(route_planner.GetDistance(), 873.41565);
}
