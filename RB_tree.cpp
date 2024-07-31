#include "RB_tree.hpp"

template <typename T>
RB_tree<T>::RB_tree (const std::initializer_list<T>& list) {
    this->_insert_from_IL(list);
}

template <typename T>
RB_tree<T>::~RB_tree () noexcept { 
    this->_clear(this->m_root);
}

template <typename T>
typename RB_tree<T>::node_pointer RB_tree<T>::_left_rotate (node_pointer x) {
    node_pointer y = x->m_right;
    x->m_right = y->m_left;

    if (y->m_left != nullptr)
        y->m_left->m_parent = x;
    y->m_parent = x->m_parent;

    if (x->m_parent == nullptr)
        this->m_root = y;
    else if (x->m_parent->m_left == x)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;

    y->m_left = x;
    x->m_parent = y;
    return y;
}

template <typename T>
typename RB_tree<T>::node_pointer RB_tree<T>::_right_rotate (node_pointer x) {
    node_pointer y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right != nullptr)
        y->m_right->m_parent = x;
    y->m_parent = x->m_parent;

    if (x->m_parent == nullptr)
        this->m_root = y;
    else if (x->m_parent->m_left == x)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;

    y->m_right = x;
    x->m_parent = y;
    return y;
}

template <typename T>
void RB_tree<T>::_insert_fix_up (node_pointer curr) {
    node_pointer uncle;

    while (curr && curr->m_parent && (curr->m_parent->m_color == _color::RED)) {
        if (curr->m_parent->m_parent) {
            if (curr->m_parent == curr->m_parent->m_parent->m_left) {
                uncle = curr->m_parent->m_parent->m_right;
                if (uncle && uncle->m_color == _color::RED) { // case 1
                    curr->m_parent->m_color = _color::BLACK;
                    uncle->m_color = _color::BLACK;
                    curr->m_parent->m_parent->m_color = _color::RED;
                    curr = curr->m_parent->m_parent;
                }
                else {
                    if (curr == curr->m_parent->m_right) { // case 2 is becoming case 3
                        curr = curr->m_parent;
                        _left_rotate(curr);
                    }
                    curr->m_parent->m_color = _color::BLACK; // case 3
                    curr->m_parent->m_parent->m_color = _color::RED;
                    _right_rotate(curr->m_parent->m_parent);
                }
            }
            else { // curr->m_parent == curr->m_parent->m_parent->right
                uncle = curr->m_parent->m_parent->m_left;
                if (uncle && uncle->m_color == _color::RED) { // case 4
                    curr->m_parent->m_color = _color::BLACK;
                    uncle->m_color = _color::BLACK;
                    curr->m_parent->m_parent->m_color = _color::RED;
                    curr = curr->m_parent->m_parent;
                }
                else {
                    if (curr == curr->m_parent->m_left) { // case 5
                        curr = curr->m_parent;
                        _right_rotate(curr);
                    }
                    curr->m_parent->m_color = _color::BLACK; // case 6
                    curr->m_parent->m_parent->m_color = _color::RED;
                    _left_rotate(curr->m_parent->m_parent);
                }
            }
        }
        this->m_root->m_color = _color::BLACK;
    }
}

template <typename T>
typename RB_tree<T>::node_pointer RB_tree<T>::_insert (const T& data, node_pointer curr) {
    node_pointer y = nullptr; // y will be prev of curr
    node_pointer to_add = new node_type(data);
    
    while (curr != nullptr) {
        y = curr;
        if (curr->m_data > data) curr = curr->m_left;
        else curr = curr->m_right;
    }

    to_add->m_parent = y;

    if (y == nullptr) {
        to_add->m_color = _color::BLACK;
        return to_add;
    }
    else if (y->m_data >= data) y->m_left = to_add;
    else y->m_right = to_add;

    _insert_fix_up(to_add);

    return this->m_root;
}

template <typename T>
void RB_tree<T>::_transplant(node_pointer u, node_pointer v) { // v's parent becomes u's parent
    if (u->m_parent == nullptr)
        this->m_root = v;
    else if (u == u->m_parent->left)
        u->m_parent->m_left = v;
    else
        u->m_parent->m_right = v;
    v->m_parent = u->m_parent;
}

template <typename T>
void RB_tree<T>::_delete_fix_up (node_pointer curr) {

}

template <typename T>
typename RB_tree<T>::node_pointer RB_tree<T>::_remove (const T& data, node_pointer root) {
    node_pointer z = this->_search(data, root);;
    node_pointer y = z;
    node_pointer x = nullptr;
    _color y_orig_color = y->m_color;

    if (z && z->m_left == nullptr) {
        x = z->m_right;
        _transplant(z, z->m_right);
    }
    else if (z && z->m_right = nullptr) {
        x = z->m_left;
        _transplant(z, z->m_left);
    }
    else {
        y = this->_find_min(z->m_right);
        y_orig_color = y->m_color;
        x = y->m_right;
        if (y->m_parent == x)
            x->m_parent = z;
        else {
            _transplant(y, y->m_right);
            y->m_right = z->m_right;
            y->m_right->m_parent = y;
        }
        _transplant(z, y);
        y->m_left = z->m_left;
        y->m_left->m_parent = y;
        y->m_color = z->m_color;
        if (y_orig_color == _color::BLACK)
            _delete_fix_up(x);
    }


    return this->m_root;
}