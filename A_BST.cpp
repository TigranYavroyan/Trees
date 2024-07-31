#include "A_BST.hpp"

template <typename T, typename m_node>
void A_BST<T, m_node>::_insert_from_IL(const std::initializer_list<T>& list) {
    for (const auto& val : list) {
        insert(val);
    }
}

template <typename T, typename m_node>
void A_BST<T, m_node>::insert(const std::initializer_list<T>& list) {
    _insert_from_IL(list);
}

template <typename T, typename m_node>
void A_BST<T, m_node>::insert (const T& data) {
    m_root = _insert(data, m_root);
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::inorder (func f) {
    if (m_root == nullptr) return;
    _inorder(f, m_root);
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::_inorder (func f, node_pointer curr) {    
    if (curr) {
        _inorder(f, curr->m_left);
        f(curr->m_data);
        _inorder(f, curr->m_right);
    }
}
template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::preorder (func f) {
    if (m_root == nullptr) return;
    _preorder(f, m_root);
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::_preorder (func f, node_pointer curr) {
    if (curr) {
        f(curr->m_data);
        _preorder(f, curr->m_left);
        _preorder(f, curr->m_right);
    }
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::postorder (func f) {
    if (m_root == nullptr) return;
    _postorder(f, m_root);
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::level_order (func f) {
    if (m_root == nullptr) return;
    _level_order (f, m_root);
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::_level_order (func f, node_pointer curr) {
    
    std::queue<node_pointer> q;
    q.push(curr);

    while (!q.empty()) {
        node_pointer tmp = q.front();

        f(tmp->m_data);

        if (tmp->m_left) q.push(tmp->m_left);
        if (tmp->m_right) q.push(tmp->m_right);

        q.pop();

    }
}

template <typename T, typename m_node>
template <typename func>
void A_BST<T, m_node>::_postorder (func f, node_pointer curr) {
    if (curr) {
        _postorder(f, curr->m_left);
        _postorder(f, curr->m_right);
        f(curr->m_data);
    }
}

template <typename T, typename m_node>
T A_BST<T, m_node>::find_min () const {
    if (m_root == nullptr)
    {
        std::cout << "There is no node_types" << std::endl;
        return T{};
    }
    return _find_min(m_root)->m_data;
}



template <typename T, typename m_node>
typename A_BST<T, m_node>::node_pointer A_BST<T, m_node>::_find_min (node_pointer curr) const {
    if (curr->m_left == nullptr) return curr;
    return _find_min(curr->m_left);
}

template <typename T, typename m_node>
T A_BST<T, m_node>::find_max () const {
    if (m_root == nullptr)
    {
        std::cout << "There is no node_types" << std::endl;
        return T{};
    }
    return _find_max(m_root)->m_data;
}

template <typename T, typename m_node>
typename A_BST<T, m_node>::node_pointer A_BST<T, m_node>::_find_max (node_pointer curr) const {
    if (curr->m_right == nullptr) return curr;
    return _find_max(curr->m_right);
}

template <typename T, typename m_node>
int A_BST<T, m_node>::height () const {
    return _height(m_root);
}

template <typename T, typename m_node>
int A_BST<T, m_node>::_height (node_pointer curr) const {
    if (curr == nullptr) return -1;
    int left_height = _height(curr->m_left);
    int right_height = _height(curr->m_right);
    return std::max(left_height, right_height) + 1;
}

template <typename T, typename m_node>
size_t A_BST<T, m_node>::size () const {
    return _size(m_root) - 1;
}

template <typename T, typename m_node>
size_t A_BST<T, m_node>::_size (node_pointer curr) const {
    if (curr == nullptr) return 1;
    else return _size(curr->m_left) + _size(curr->m_right);
}

template <typename T, typename m_node>
bool A_BST<T, m_node>::find (const T& data) const {
    if (m_root == nullptr) return false;
    return _find(data, m_root);
}

template <typename T, typename m_node>
bool A_BST<T, m_node>::_find (const T& data, node_pointer curr) const {
    if (curr == nullptr) return
false;
    if (curr->m_data == data) return true;
    if (curr->m_data < data) return _find(data, curr->m_right);
    else return _find(data, curr->m_left);
}

template <typename T, typename m_node>
void A_BST<T, m_node>::remove (const T& data) {
    if (m_root == nullptr) return;
    m_root = _remove(data, m_root);
}

template <typename T, typename m_node>
typename A_BST<T, m_node>::node_pointer A_BST<T, m_node>::_search(const T& data, node_pointer curr) const {
    if (curr == nullptr) return curr;
    if (curr->m_data == data) return curr;
    if (curr->m_data < data) return _search(data, curr->m_right);
    else return _search(data, curr->m_left);
}

template <typename T, typename m_node>
T A_BST<T, m_node>::successor (const T& data) const {
    node_pointer res = _successor(_search(data, m_root));
    return (res) ? res->m_data : throw std::invalid_argument("There is no successor");

}

template <typename T, typename m_node>
typename A_BST<T, m_node>::node_pointer A_BST<T, m_node>::_successor (node_pointer curr) const {
    if (curr == nullptr) return nullptr;
    if (curr->m_right) return _find_min(curr->m_right);

    node_pointer anc = m_root;
    node_pointer succ = nullptr;

    while (anc != curr) {
        if (anc->m_data > curr->m_data) {
            succ = anc;
            anc = anc->m_left;
        }
        else anc = anc->m_right;
    }

    return succ;
}

template <typename T, typename m_node>
T A_BST<T, m_node>::predecessor (const T& data) const {
    node_pointer res = _predecessor(_search(data, m_root));
    return (res) ? res->m_data : throw std::invalid_argument("There is no predecessor");
}

template <typename T, typename m_node>
typename A_BST<T, m_node>::node_pointer A_BST<T, m_node>::_predecessor (node_pointer curr) const {
    if (curr == nullptr) return nullptr;
    if (curr->m_left) return _find_max(curr->m_left);

    node_pointer anc = m_root;
    node_pointer pred = nullptr;
    while (anc != curr) {
        if (anc->m_data < curr->m_data) {
            pred = anc;
            anc = anc->m_right;
        }
        else anc = anc->m_left;
    }

    return pred;
}

template <typename T, typename m_node>
void A_BST<T, m_node>::clear () noexcept {
    _clear(m_root);
    m_root = nullptr;
}

template <typename T, typename m_node>
void A_BST<T, m_node>::_clear (node_pointer& curr) noexcept {
    if (curr) {
        _clear(curr->m_left);
        _clear(curr->m_right);
        delete curr;
    }
}