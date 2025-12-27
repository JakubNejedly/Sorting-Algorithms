#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>

template <typename T>
class TreeNode {
public:
    TreeNode(T data);
 
    const T& getData() const;

    void setLeft(std::unique_ptr<TreeNode<T>> left);
    std::unique_ptr<TreeNode<T>>& getLeft();

    void setRight(std::unique_ptr<TreeNode<T>> right);
    std::unique_ptr<TreeNode<T>>& getRight();

    uint32_t calculateDepth() const;
    int32_t calculateBalance() const;

protected:
    const T m_data;

    std::unique_ptr<TreeNode<T>> m_left;
    std::unique_ptr<TreeNode<T>> m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T data)
: m_data(std::move(data))
{}


template <typename T>
const T& TreeNode<T>::getData() const {
    return m_data;
}

template <typename T>
void TreeNode<T>::setLeft(std::unique_ptr<TreeNode<T>> left) {
    m_left = std::move(left);
}

template <typename T>
std::unique_ptr<TreeNode<T>>& TreeNode<T>::getLeft() {
    return m_left;
}


template <typename T>
void TreeNode<T>::setRight(std::unique_ptr<TreeNode<T>> right) {
    m_right = std::move(right);
}

template <typename T>
std::unique_ptr<TreeNode<T>>& TreeNode<T>::getRight() {
    return m_right;
}

template <typename T>
uint32_t TreeNode<T>::calculateDepth() const {
    uint32_t leftDepth = (m_left) ? m_left->calculateDepth() : 0;
    uint32_t rightDepth = (m_right) ? m_right->calculateDepth() : 0;
    return 1 + std::max(leftDepth, rightDepth);
}

template <typename T>
int32_t TreeNode<T>::calculateBalance() const {
    uint32_t leftDepth = (m_left) ? m_left->calculateDepth() : 0;
    uint32_t rightDepth = (m_right) ? m_right->calculateDepth() : 0;
    return static_cast<int32_t>(leftDepth) - rightDepth;
}