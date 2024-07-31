#ifndef BST_HPP
#define BST_HPP

#include "A_BST.hpp"

template <typename T>
class BST final : public A_BST<T, Node<T> > {
public:
    using node_type = Node<T>;
    using node_pointer = Node<T>*;
private:
    node_pointer _insert(const T&, node_pointer) override;
    node_pointer _remove(const T&, node_pointer) override;
public:
    BST () = default;
    BST (const std::initializer_list<T>&);
    virtual ~BST () noexcept;
};

#include "BST.cpp"

#endif // BST_HPP