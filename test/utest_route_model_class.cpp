#include "test.hpp"

// Test that the path size is zero initially.
TEST_F(RouteModelTest, RouteModelData) {
    EXPECT_EQ(model.path.size(), 0);
    EXPECT_EQ(model.Nodes().size(), 10754);
    ASSERT_EQ(model.SNodes().size(), 10754);
}
