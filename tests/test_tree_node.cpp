#include <gtest/gtest.h>
#include "TreeNode.hpp"

class TreeNodeTest : public ::testing::Test {};

TEST_F(TreeNodeTest, NodeInitialization) {
    TreeNode<int32_t> node(100);
    EXPECT_EQ(node.getData(), 100);
}

TEST_F(TreeNodeTest, DepthCalculationWithChildren) {
    auto root = std::make_unique<TreeNode<int32_t>>(10);
    EXPECT_EQ(root->calculateDepth(), 1);

    root->setLeft(std::make_unique<TreeNode<int32_t>>(5));
    EXPECT_EQ(root->calculateDepth(), 2);
    root->setRight(std::make_unique<TreeNode<int32_t>>(15));
    EXPECT_EQ(root->calculateDepth(), 2);
}

TEST_F(TreeNodeTest, DepthCalculationMultipleLevels) {
    auto root = std::make_unique<TreeNode<int32_t>>(10);
    root->setLeft(std::make_unique<TreeNode<int32_t>>(5));
    root->getLeft()->setLeft(std::make_unique<TreeNode<int32_t>>(2));
    EXPECT_EQ(root->calculateDepth(), 3);

    root->setRight(std::make_unique<TreeNode<int32_t>>(15));
    root->getRight()->setRight(std::make_unique<TreeNode<int32_t>>(20));
    root->getRight()->getRight()->setRight(std::make_unique<TreeNode<int32_t>>(25));
    EXPECT_EQ(root->calculateDepth(), 4);
}
