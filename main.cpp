#include "AVL.hpp"
#include "BST.hpp"
#include "RB_tree.hpp"

int main () {
    std::initializer_list<int> il1 = {2, 1, -2, -5, -1, 5, 4, 8, 7, 9};
    std::initializer_list<int> il2 = {72, 73, 74, 66, 65, 69, 67, 70, 68};
    std::initializer_list<int> il3 = {12, 9, 15, 13, 16, 10, 8};
    std::initializer_list<int> il4 = {0, 5, 10, 20, 30, 29, 28, 27, 26, 25, 21, 22, 23, 24};
    RB_tree<int> tree = il4;
    tree.remove(28);
    // AVL<int> a_tree = il2;
    // BST<int> tree = il4;
    // tree.level_order([](const int val){std::cout << val << ' ';});
    // std::cout << '\n';
    tree.preorder([](const int val){std::cout << val << ' ';});
    std::cout << '\n';
    // tree.postorder([](const int val){std::cout << val << ' ';});
    // std::cout << '\n';
    // tree.inorder([](const int val){std::cout << val << ' ';});
    // std::cout << '\n' << tree.successor(24) << std::endl;
    std::cout << "\nThe height: " << tree.height() << '\n';
    // a_tree.postorder([](const int val){std::cout << val << ' ';});
    // std::cout << "\nThe height: " << a_tree.height() << '\n';
}