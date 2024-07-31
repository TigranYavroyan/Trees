#ifndef A_BST_HPP
#define A_BST_HPP
#include <iostream>
#include <queue>
#include <vector>

enum class _color {RED, BLACK};

template <typename T>
struct Node
{
    T m_data;
    Node<T>* m_left;
    Node<T>* m_right;

    Node () : m_left{nullptr}, m_right{nullptr}, m_data{T{}} {}
    Node (const T& data) : m_left{nullptr}, m_right{nullptr}, m_data{data} {}
};

template <typename T>
struct RB_Node {
    T m_data;
    _color m_color;
    RB_Node<T>* m_left;
    RB_Node<T>* m_right;
    RB_Node<T>* m_parent;

    RB_Node () : m_left{nullptr}, m_right{nullptr}, m_parent{nullptr}, m_data{T{}}, m_color{_color::RED} {}
    RB_Node (const T& data) : m_left{nullptr}, m_right{nullptr}, m_parent{nullptr}, m_data{data}, m_color{_color::RED} {}
    RB_Node (_color color) : m_left{nullptr}, m_right{nullptr}, m_parent{nullptr}, m_data{T{}}, m_color{color} {}

    RB_Node (RB_Node<T>* nil, _color color, const T& data) : m_left{nil}, m_right{nil}, m_parent{nil}, m_data{data}, m_color{color} {}
    RB_Node (RB_Node<T>* nil, const T& data) : RB_Node (nil, _color::RED, data) {}
    RB_Node (RB_Node<T>* nil, _color color) : RB_Node (nil, color, T{}) {}
    RB_Node (RB_Node<T>* nil) : RB_Node (nil, _color::RED, T{}) {}
};

template <typename T, typename m_node = Node<T> >
class A_BST
{
public:
    using node_type = m_node;
    using node_pointer = m_node*;
protected:
    node_pointer m_root = nullptr;

    node_pointer _search (const T&, node_pointer) const;
    void _insert_from_IL (const std::initializer_list<T>&);

    virtual node_pointer _insert (const T&, node_pointer) = 0;
    virtual node_pointer _remove (const T&, node_pointer) = 0;
    bool _find (const T&, node_pointer) const;

    template <typename func>
    void _inorder (func f, node_pointer);

    template <typename func>
    void _preorder (func f, node_pointer);

    template <typename func>
    void _postorder (func f, node_pointer);

    template <typename func>
    void _level_order (func f, node_pointer);

    node_pointer _find_min (node_pointer) const;
    node_pointer _find_max (node_pointer) const;
    node_pointer _successor (node_pointer) const;
    node_pointer _predecessor (node_pointer) const;
    int _height (node_pointer) const;
    size_t _size (node_pointer) const;
    void _clear(node_pointer&) noexcept;
public:
    virtual ~A_BST () noexcept = default;
    void insert (const T&);
    void insert (const std::initializer_list<T>&);
    void remove (const T&);
    bool find (const T&) const;

    template <typename func>
    void inorder (func f);

    template <typename func>
    void preorder (func f);

    template <typename func>
    void postorder (func f);

    template <typename func>
    void level_order (func f);

    T find_min () const;
    T find_max () const;
    T successor (const T&) const;
    T predecessor (const T&) const;
    int height () const;
    size_t size () const;
    void clear () noexcept;
};

#include "A_BST.cpp"

#endif // BST_HPP