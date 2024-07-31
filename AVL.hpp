#ifndef AVL_HPP
#define AVL_HPP

#include "A_BST.hpp"

template <typename T>
class AVL final : public A_BST<T, Node<T> > {
public:
    using node_type = Node<T>;
    using node_pointer = Node<T>*;
private:
    node_pointer _left_rotate (node_pointer z);
    node_pointer _right_rotate (node_pointer z);
    int       _get_BF(node_pointer curr);

    node_pointer _insert(const T&, node_pointer) override;
    node_pointer _remove(const T&, node_pointer) override;
public:
    AVL () = default;
    AVL (const std::initializer_list<T>&);
    ~AVL () noexcept;
};

#include "AVL.cpp"

#endif // AVL_HPP