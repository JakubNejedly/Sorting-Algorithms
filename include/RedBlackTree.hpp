#pragma once

#include "BinarySortingTree.hpp"
#include "RBTreeNode.hpp"

namespace adsc {

template <typename T, typename Comparator = std::less<T>>
class RedBlackTree : public BinarySortingTree<T, Comparator> {
public:
    RedBlackTree(Comparator comparator = Comparator())
        : BinarySortingTree<T, Comparator>(comparator) {}

    void insert(T data) override;

private:
    
};

} // namespace adsc