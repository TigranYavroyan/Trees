#include "BST.hpp"

template <typename T>
typename BST<T>::node_pointer BST<T>::_insert (const T& data, node_pointer curr) {
    if (curr == nullptr) return new node_type(data);
    else if (curr->m_data < data) curr->m_right = _insert(data, curr->m_right);
    else curr->m_left = _insert(data, curr->m_left);

    return curr;
}

template <typename T>
typename BST<T>::node_pointer BST<T>::_remove (const T& data, node_pointer curr) {
    if (curr == nullptr) return curr;
    if (curr->m_data > data) curr->m_left = _remove(data, curr->m_left);
    else if (curr->m_data < data) curr->m_right = _remove(data, curr->m_right);
    else {
        node_pointer tmp;
        if (curr->m_left == nullptr) {
            tmp = curr->m_right;
            delete curr;
            return tmp;
        }
        else if (curr->m_right == nullptr) {
            tmp = curr->m_left;
            delete curr;
            return tmp;
        }
        else {
            tmp = this->_find_min(curr->m_right);
            curr->m_data = tmp->m_data;
            curr->m_right = _remove(tmp->m_data, curr->m_right);
        }
    }

    return curr;
}

template <typename T>
BST<T>::BST (const std::initializer_list<T>& list) {
    this->_insert_from_IL(list);
}

template <typename T>
BST<T>::~BST () noexcept { this->_clear(this->m_root); }