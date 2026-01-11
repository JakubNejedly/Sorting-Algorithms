#pragma once

#include <cstdint>
#include <memory>

namespace adsc {

enum class NodeColor {
    RED,
    BLACK
};

template <typename T>
struct RBTreeNode {
    T m_data;
    uint32_t m_count;
    NodeColor m_color;
    
    RBTreeNode<T>* m_parent; 
    
    std::unique_ptr<RBTreeNode<T>> m_left;
    std::unique_ptr<RBTreeNode<T>> m_right;

    RBTreeNode(T data, RBTreeNode<T>* parent = nullptr)
        : m_data(std::move(data))
        , m_count(1)
        , m_color(NodeColor::RED)
        , m_parent(parent)
        , m_left(nullptr)
        , m_right(nullptr)
        {}
};

} // namespace adsc
