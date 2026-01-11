#pragma once

#include "SortingTree.hpp"

template <typename T, typename Comparator = std::less<T>>
class BinaryTree : public SortingTree<T, Comparator> {
public:
    BinaryTree(Comparator comparator = Comparator());

    virtual ~BinaryTree() = default;

    virtual void insert(T data) override;
    virtual void remove(const T& data) override;
    virtual T removeMin() override;
    virtual T removeMax() override;

protected:
    using SortingTree<T, Comparator>::m_root;
    using SortingTree<T, Comparator>::m_comparator;

    using TreeNodePtr = std::unique_ptr<TreeNode<T>>;

private:
    // Helper for insert
    void recursive_insert(TreeNodePtr& node, T data);
    
    // Helpers for remove
    void recursive_remove(TreeNodePtr& node, const T& data);
    TreeNodePtr extractMin(TreeNodePtr& node);
    
    // Helper for removeMin
    T recursive_remove_min(TreeNodePtr& node);

    // Helper for removeMax
    T recursive_remove_max(TreeNodePtr& node);
};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(Comparator comparator)
: SortingTree<T, Comparator>(comparator)
{}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::insert(T data) {
    this->m_elementsCount++;
    recursive_insert(m_root, std::move(data));
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::recursive_insert(TreeNodePtr& node, T data) {
    if (!node) {
        this->m_nodesCount++;
        node = std::make_unique<TreeNode<T>>(std::move(data));
        return;
    }

    if (data == node->getData()) {
        node->incrementCount();
    }else {
        if (m_comparator(data, node->getData())) {
            recursive_insert(node->getLeft(), std::move(data));
        } else {
            recursive_insert(node->getRight(), std::move(data));
        }
    }

    node->updateHeight();
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::remove(const T& data) {
    recursive_remove(m_root, data);
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::recursive_remove(TreeNodePtr& node, const T& data) {
    if (!node){
        // Record not found
        return;
    }

    if (m_comparator(data, node->getData())) {
        recursive_remove(node->getLeft(), data);
    } else if (m_comparator(node->getData(), data)) {
        recursive_remove(node->getRight(), data);
    } else {
        // Data found
        if (node->decrementCount()) {
            this->m_elementsCount--;
            return;
        }

        // Remove node with only no or one child
        this->m_elementsCount--;
        this->m_nodesCount--;  
        if (!node->getLeft()) {
            // Only right child case
            node = std::move(node->getRight());
            return;
        } 
        else if (!node->getRight()) {
            // Only left child case
            node = std::move(node->getLeft());
            return;
        } 
        else {
            // Two children case
            TreeNodePtr successor = extractMin(node->getRight());
            successor->setLeft(std::move(node->getLeft()));
            successor->setRight(std::move(node->getRight()));
            node = std::move(successor);
        }
    }

    node->updateHeight();
}

template <typename T, typename Comparator>
typename BinaryTree<T, Comparator>::TreeNodePtr
BinaryTree<T, Comparator>::extractMin(TreeNodePtr& node) {
    if (node->getLeft()) {
        TreeNodePtr minNode = extractMin(node->getLeft());
        node->updateHeight();
        return minNode;
    }

    TreeNodePtr minNode = std::move(node);
    node = std::move(minNode->getRight()); 
    return minNode;
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::removeMin() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }
    this->m_elementsCount--;
    return std::move(recursive_remove_min(m_root));
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::recursive_remove_min(TreeNodePtr& node) {
    // Iterate to find min value
    if (node->getLeft()) {
        T outData = std::move(recursive_remove_min(node->getLeft()));
        node->updateHeight();
        return std::move(outData);
    }

    T outData = std::move(node->getData());
    if (node->decrementCount()) {
        // Only decrement count
        return std::move(outData);
    }
    // Replace node with its right child
    this->m_nodesCount--;
    node = std::move(node->getRight());
    return std::move(outData);
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::removeMax() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }
    this->m_elementsCount--;
    return std::move(recursive_remove_max(m_root));
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::recursive_remove_max(TreeNodePtr& node) {
    // Iterate to find max value
    if (node->getRight()) {
        T outData = std::move(recursive_remove_max(node->getRight()));
        node->updateHeight();
        return std::move(outData);
    }

    T outData = std::move(node->getData());
    if (node->decrementCount()) {
        // Only decrement count
        return std::move(outData);
    }
    // Replace node with its left child
    this->m_nodesCount--;
    node = std::move(node->getLeft());  
    return std::move(outData);
}