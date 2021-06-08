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

#include <stdexcept>
#include "memory"
using namespace std;

#include "sources/BinaryTree.hpp"
using namespace ariel;

int main() {

    //            BinaryTree &bootstrap() {
//                this->add_root(1);
//                this->root->left = std::shared_ptr<Node>(new Node(2));
//                this->root->right = std::shared_ptr<Node>(new Node(3));
//
//                this->root->left->parent = this->root;
//                this->root->right->parent = this->root;
//
//                this->root->left->left = std::shared_ptr<Node>(new Node(4));
//                this->root->left->left->parent = this->root->left;
//                this->root->left->right = std::shared_ptr<Node>(new Node(5));
//                this->root->left->right->parent = this->root->left;
//
////                this->root->left->right->left = std::shared_ptr<Node>(new Node(6));
////                this->root->left->right->left->parent = this->root->left->right;
//
//                return *this;
//            }
//


    BinaryTree<int> tree;
    int adder = 0;
    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);
    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);

//
    BinaryTree<int> tree2;
    tree2=tree;

//    tree2.add_root(44444);
    vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};


    BinaryTree<int>::iterator it2 = tree2.begin_preorder();
    BinaryTree<int>::iterator theend = tree2.end_preorder();
//    for(int i =0; i < 8 ; i++){
//        ++it2;
//    }
//
//
////    std::cout <<( it2 == theend )<< std::endl;
////    std::cout << *it2<< std::endl;
//    ++it2;

    while(it2 != tree2.end_preorder()){
        std::cout << *it2 << std::endl;
        ++it2;
    }
//    return 0;
//
//
//    BinaryTree<int> tree_of_ints;
////    tree_of_ints.add_root(1);
//tree_of_ints.bootstrap();
//    BinaryTree<int>::iterator it = tree_of_ints.begin_postorder()   ;
//
//    int  count = 0;
//
//
//    tree_of_ints.add_left(2, 123);
//    while(it != tree_of_ints.end_postorder()){
//        std::cout << *it << " " << std::endl;
//        ++it;
//        ++count;
//    }
//
////    it = new Node();
////    BinaryTree<int>::Node n;
////    n.left = std::unique_ptr<BinaryTree<int>::Node>(new BinaryTree<int>::Node());
//
////    tree_of_ints.add_root(1)
////            .add_left(1, 9)      // Now 9 is the left child of 1
////            .add_left(9, 4)      // Now 4 is the left child of 9
////            .add_right(9, 5)     // Now 5 is the right child of 9
////            .add_right(1, 3)     // Now 3 is the right child of 1
////            .add_left(1, 2);     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
////
////    cout << tree_of_ints << endl;  /* Prints the tree in a reasonable format. For example:
////        1
////        |--------|
////        2        3
////        |---|
////        4   5
////  */
////
////    for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 1 2 4 5 3
////    for (auto it=tree_of_ints.begin_inorder(); it!=tree_of_ints.end_inorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 4 2 5 1 3
////    for (auto it=tree_of_ints.begin_postorder(); it!=tree_of_ints.end_postorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 4 5 2 3 1
////
////    for (int element: tree_of_ints) {  // this should work like inorder
////        cout << element << " " ;
////    }  // prints: 4 2 5 1 3
////
////
////    // The same should work with other types, e.g. with strings:
////
////    BinaryTree<string> tree_of_strings;
////    tree_of_strings.add_root("1")
////            .add_left("1", "9")      // Now 9 is the left child of 1
////            .add_left("9", "4")      // Now 4 is the left child of 9
////            .add_right("9", "5")     // Now 5 is the right child of 9
////            .add_right("1", "3")     // Now 3 is the right child of 1
////            .add_left("1", "2");     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
////    cout << tree_of_strings << endl;
////
////    for (auto it=tree_of_strings.begin_preorder(); it!=tree_of_strings.end_preorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 1 2 4 5 3
////    for (auto it=tree_of_strings.begin_inorder(); it!=tree_of_strings.end_inorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 4 2 5 1 3
////    for (auto it=tree_of_strings.begin_postorder(); it!=tree_of_strings.end_postorder(); ++it) {
////        cout << (*it) << " " ;
////    }  // prints: 4 5 2 3 1
////
////    // demonstrate the arrow operator:
////    for (auto it=tree_of_strings.begin_postorder(); it!=tree_of_strings.end_postorder(); ++it) {
////        cout << it->size() << " " ;
////    }  // prints: 1 1 1 1 1
////
////
////    for (const string& element: tree_of_strings) {  // this should work like inorder
////        cout << element << " " ;
////    }   // prints: 4 2 5 1 3

}