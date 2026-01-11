#include <gtest/gtest.h>
#include "AVLTree.hpp"

#include <queue>
#include <vector>

class AVLTreeTest : public ::testing::Test {
protected:
    AVLTree<int> avl;
};


TEST_F(AVLTreeTest, RightRotationL) {
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getHeight(), 2);
}


TEST_F(AVLTreeTest, LeftRotationR) {
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getHeight(), 2);
}

TEST_F(AVLTreeTest, DoubleRotationLR) {
    avl.insert(30);
    avl.insert(10);
    avl.insert(20);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
}

TEST_F(AVLTreeTest, DoubleRotationRL) {
    avl.insert(10);
    avl.insert(30);
    avl.insert(20);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
}

TEST_F(AVLTreeTest, HeightAfterMultipleInsertions) {
    for (int x : {50, 30, 70, 20, 40, 60, 80}) {
        avl.insert(x);
    }

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getHeight(), 3);
}

TEST_F(AVLTreeTest, RemoveLeafTriggersRotation) {
    avl.insert(20);
    avl.insert(10);
    avl.insert(30);
    avl.insert(25);
    
    avl.remove(10);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 25);
    EXPECT_EQ(avl.getRoot()->getHeight(), 2);
    EXPECT_EQ(avl.nodesCount(), 3);
}

TEST_F(AVLTreeTest, RemoveMinWithRebalance) {
    for (int x : {10, 20, 30, 40, 50}) avl.insert(x);
    EXPECT_EQ(avl.getRoot()->getHeight(), 3);

    EXPECT_EQ(avl.removeMin(), 10);
    EXPECT_EQ(avl.removeMin(), 20);

    EXPECT_LE(avl.getRoot()->getHeight(), 2);
    EXPECT_EQ(avl.nodesCount(), 3);
    EXPECT_EQ(avl.getRoot()->getData(), 40);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 50);
}

TEST_F(AVLTreeTest, RemoveMaxWithRebalance) {
    for (int x : {50, 40, 30, 20, 10}) avl.insert(x);
    
    EXPECT_EQ(avl.removeMax(), 50);
    EXPECT_EQ(avl.removeMax(), 40);

    EXPECT_LE(avl.getRoot()->getHeight(), 2);
    EXPECT_EQ(avl.nodesCount(), 3);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
}

TEST_F(AVLTreeTest, RemoveNodeWithTwoChildrenAVL) {
    for (int x : {50, 25, 75, 15, 35, 65, 85}) avl.insert(x);
    
    avl.remove(50);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.elementsCount(), 6);
    EXPECT_LE(avl.getRoot()->getHeight(), 3);
    EXPECT_EQ(avl.getRoot()->getData(), 65);
}

TEST_F(AVLTreeTest, CascadingRotations) {
    for (int x : {50, 25, 80, 10, 30, 60, 90, 5, 15, 27, 35, 55}) avl.insert(x);
    
    avl.remove(90);
    
    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_LE(avl.getRoot()->getHeight(), 4);
    EXPECT_EQ(avl.getRoot()->getData(), 50);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 25);
    EXPECT_EQ(avl.getRoot()->getLeft()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getLeft()->getRight()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 60);
    EXPECT_EQ(avl.getRoot()->getRight()->getLeft()->getData(), 55);
    EXPECT_EQ(avl.getRoot()->getRight()->getRight()->getData(), 80);
}

TEST_F(AVLTreeTest, CompareWithPriorityQueue) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    
    std::vector<int> testData = {
        42, 17, 42, 1, 99, 15, 8, 42, 23, 7, 
        10, 5, 88, 31, 12, 15, 6, 3, 50, 21
    };

    for (int val : testData) {
        avl.insert(val);
        pq.push(val);
    }

    EXPECT_EQ(avl.elementsCount(), 20);
    EXPECT_EQ(avl.nodesCount(), 17);

    for (int i = 0; i < 20; ++i) {
        int avlMin = avl.removeMin();
        int pqMin = pq.top();
        pq.pop();

        EXPECT_EQ(avlMin, pqMin) << "Mismatch at index " << i;
    }

    EXPECT_TRUE(avl.empty());
    EXPECT_TRUE(pq.empty());
}