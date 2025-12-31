#include <gtest/gtest.h>

#include <algorithm>

#include "BinaryTree.hpp"

class BinaryTreeTest : public ::testing::Test {
protected:
    BinaryTree<int> tree;

    // Standard tree filling
    void fillStandard() {
        for (int x : {50, 25, 75, 10, 30}) tree.insert(x);
    }

    // Linear left filling
    void fillSkewed() {
        for (int x : {50, 40, 30, 20, 10}) tree.insert(x);
    }

    // Filling with duplicates
    void fillDuplicates() {
        for (int x : {50, 50, 50, 20, 20, 80}) tree.insert(x);
    }
};

TEST_F(BinaryTreeTest, IsEmpty) {
    BinaryTree<uint32_t> tree;
    EXPECT_TRUE(tree.empty());
    tree.insert(10);
    EXPECT_FALSE(tree.empty());
}

TEST_F(BinaryTreeTest, BasicInsertion) {
    BinaryTree<int32_t> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_EQ(tree.getRoot()->getData(), 10);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData(), 5);
    EXPECT_EQ(tree.getRoot()->getRight()->getData(), 15);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getLeft()->getRight(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight(), nullptr);
}

TEST_F(BinaryTreeTest, DecrementCountTest) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(50); 

    tree.remove(50); 
    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getCount(), 1);

    tree.remove(50);
    EXPECT_EQ(tree.getRoot(), nullptr);
}

TEST_F(BinaryTreeTest, MetricsReflectReality) {
    fillDuplicates();
    EXPECT_EQ(tree.nodesCount(), 3);
    EXPECT_EQ(tree.elementsCount(), 6);

    tree.remove(50);
    tree.remove(50);
    EXPECT_EQ(tree.nodesCount(), 3);
    EXPECT_EQ(tree.elementsCount(), 4);

    tree.remove(50);
    EXPECT_EQ(tree.nodesCount(), 2);
    EXPECT_EQ(tree.elementsCount(), 3);
}

TEST_F(BinaryTreeTest, RemoveMinWithMultipleCounts) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(10);
    tree.insert(20);

    EXPECT_EQ(tree.removeMin(), 10);
    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getCount(), 1);


    EXPECT_EQ(tree.removeMin(), 10);
    EXPECT_EQ(tree.getRoot()->getData(), 20);
    EXPECT_EQ(tree.getRoot()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight(), nullptr);
}

TEST_F(BinaryTreeTest, RemoveNodeWithTwoChildren) {
    fillStandard(); 
    tree.remove(25);

    EXPECT_EQ(tree.nodesCount(), 4);
    EXPECT_EQ(tree.getRoot()->getData(), 50);
    ASSERT_NE(tree.getRoot()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData(), 30);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getData(), 10);
}

TEST_F(BinaryTreeTest, RemoveLeafNodeByValue) {
    fillStandard(); 
    
    EXPECT_EQ(tree.nodesCount(), 5);
    tree.remove(10);
    
    EXPECT_EQ(tree.nodesCount(), 4);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData(), 25);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft(), nullptr);
}

TEST_F(BinaryTreeTest, RemoveNodeWithOnlyLeftChild) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(10);
    
    tree.remove(30);
    
    ASSERT_NE(tree.getRoot()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(tree.nodesCount(), 2);
}

TEST_F(BinaryTreeTest, RemoveNodeWithOnlyRightChild) {
    tree.insert(50);
    tree.insert(70);
    tree.insert(90);
    
    tree.remove(70);
    
    ASSERT_NE(tree.getRoot()->getRight(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight()->getData(), 90);
    EXPECT_EQ(tree.nodesCount(), 2);
}

TEST_F(BinaryTreeTest, RemoveRootWithOneChild) {
    tree.insert(50);
    tree.insert(70);
    
    tree.remove(50);
    
    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getData(), 70);
    EXPECT_EQ(tree.nodesCount(), 1);
}

TEST_F(BinaryTreeTest, SequentialMinMaxRemoval) {
    fillStandard();

    EXPECT_EQ(tree.removeMin(), 10);
    EXPECT_EQ(tree.removeMax(), 75);
    EXPECT_EQ(tree.nodesCount(), 3);
    
    EXPECT_EQ(tree.removeMin(), 25);
    EXPECT_EQ(tree.removeMin(), 30);
    EXPECT_EQ(tree.removeMin(), 50);
    
    EXPECT_TRUE(tree.empty());
}

TEST_F(BinaryTreeTest, RemoveRootNode) {
    tree.insert(10);
    tree.insert(20);
    tree.remove(10); 

    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getData(), 20);
    EXPECT_EQ(tree.nodesCount(), 1);
}

TEST_F(BinaryTreeTest, StressTestRandomInserts) {
    std::vector<int> values = {42, 7, 19, 88, 3, 50, 1, 100, 25};
    for (int v : values) tree.insert(v);

    std::sort(values.begin(), values.end());

    for (int expected : values) {
        EXPECT_EQ(tree.removeMin(), expected);
    }
    EXPECT_TRUE(tree.empty());
}

struct LengthComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

TEST(BinaryTreeGenericTest, StringLengthComparator) {
    BinaryTree<std::string, LengthComparator> tree;

    tree.insert("A");
    tree.insert("AAA");
    tree.insert("AA");

    EXPECT_EQ(tree.getRoot()->getData(), "A");
    EXPECT_EQ(tree.getRoot()->getRight()->getData(), "AAA");
    EXPECT_EQ(tree.getRoot()->getRight()->getLeft()->getData(), "AA");

    tree.insert("AAA");

    EXPECT_EQ(tree.removeMin(), "A");
    EXPECT_EQ(tree.nodesCount(), 2);
    EXPECT_EQ(tree.getRoot()->getData(), "AAA");
    EXPECT_EQ(tree.getRoot()->getCount(), 2);
}

TEST(BinaryTreeGenericTest, StringEqualityWithComparator) {
    BinaryTree<std::string, LengthComparator> tree;

    tree.insert("Foo");
    tree.insert("Foo");
    
    tree.insert("Bar");
    tree.insert("Cat");

    EXPECT_EQ(tree.nodesCount(), 3);
    EXPECT_EQ(tree.elementsCount(), 4);
}