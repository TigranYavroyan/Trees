#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "A_BST.hpp"

template <typename T>
class RB_tree final : public A_BST<T, RB_Node<T> > {
public:
    using node_type = RB_Node<T>;
    using node_pointer = RB_Node<T>*;
private:
    node_pointer _left_rotate (node_pointer);
    node_pointer _right_rotate (node_pointer);
    void _insert_fix_up (node_pointer);
    void _transplant (node_pointer, node_pointer);
    void _delete_fix_up (node_pointer);

    node_pointer _insert (const T&, node_pointer) override;
    node_pointer _remove (const T&, node_pointer) override;
public:
    RB_tree () = default;
    RB_tree (const std::initializer_list<T>&);
    ~RB_tree () noexcept;
};

#include "RB_tree.cpp"

#endif // RB_TREE_HPP