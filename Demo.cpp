/**
 * Demo file for the exercise on binary tree
 *
 * @author Erel Segal-Halevi
 * @since 2021-04
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "memory"
#include "sources/BinaryTree.hpp"

using namespace ariel;

int main() {

    std::cout << "Generating first tree" << std::endl;
    BinaryTree<int> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1);
    tree.add_left(1, 2);
    tree.add_right(1, 3);
    tree.add_left(2, 4);
    tree.add_right(2, 5);
    tree.add_left(5, 10);
    tree.add_right(5, 11);
    tree.add_left(10, 20);
    tree.add_right(11, 23);
    std::cout << tree << std::endl;

    std::cout << "Deep copying tree to tree2" << std::endl;
    BinaryTree<int> tree2(tree);
    std::cout << tree2 << std::endl;

    std::cout << "Are trees permutations? " << std::boolalpha << std::is_permutation(tree.begin_preorder(), tree.end_preorder(), tree2.begin_preorder()) << std::endl;

    std::cout << "Modifying tree2" << std::endl;
    tree2.add_left(10, 2222222);
    std::cout << tree2 << std::endl;

    std::cout << "Are trees permutations? " << std::boolalpha << std::is_permutation(tree.begin_preorder(), tree.end_preorder(), tree2.begin_preorder()) << std::endl;
    std::cout << tree << std::endl;
    std::cout << tree2 << std::endl;

}