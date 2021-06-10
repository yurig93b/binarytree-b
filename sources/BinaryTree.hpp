//
// Created by Yuri Grigorian on 08/06/2021.
//

#ifndef BINARYTREE_B_BINARYTREE_HPP
#define BINARYTREE_B_BINARYTREE_HPP

#include <memory>
#include <sstream>
#include <ios>
#include <iostream>
#include "TraverseType.hpp"

namespace ariel {
    template<typename T>
    class BinaryTree {

            ///////////// Node /////////////
            struct Node {

                std::unique_ptr <T> val;
                std::weak_ptr <Node> parent;
                std::shared_ptr <Node> left;
                std::shared_ptr <Node> right;
                int visit_id; // Used to distinguish between multiple iterators running

                Node() : visit_id(-1) {};

                Node(const T &_val) {
                    val = std::make_unique<T>(_val);
                    visit_id = -1;
                }

                /// Set the left child with a val, creates if needed.
                /// \param _parent sptr for parent
                /// \param _val value
                /// \return Node
                Node &set_left(std::shared_ptr <Node> _parent, T _val) {
                    if (!this->left) {
                        this->left = std::shared_ptr<Node>(new Node(_val));
                        this->left->parent = _parent;
                    } else {
                        this->left->val = std::make_unique<T>(_val);
                    }

                    return *this;
                }

                /// Set the right child with a val, creates if needed.
                /// \param _parent sptr for parent
                /// \param _val value
                /// \return Node
                Node &set_right(std::shared_ptr <Node> _parent, T _val) {
                    if (!this->right) {
                        this->right = std::shared_ptr<Node>(new Node(_val));
                        this->right->parent = _parent;
                    } else {
                        this->right->val = std::make_unique<T>(_val);
                    }

                    return *this;
                }

            };

            std::shared_ptr <Node> root;

            /// Adds a a child left or right by value.
            /// \param existing needed existing value.
            /// \param new_child_val new child value.
            /// \param left_toggle true for left else false.
            /// \return this.
            BinaryTree &_add(const T &existing, const T &new_child_val, bool left_toggle) {
                iterator it = this->begin_inorder();
                while (it != this->end_inorder()) {

                    // Found needed val
                    if (*it == existing) {
                        if (left_toggle) {
                            it.get_node_parent_sptr()->set_left(it.get_node_parent_sptr(), new_child_val);
                        } else {
                            it.get_node_parent_sptr()->set_right(it.get_node_parent_sptr(), new_child_val);
                        }
                        return *this;
                    }
                    ++it;
                }

                throw std::runtime_error("Could not find passed existing value ");
            }

        public:
            ~BinaryTree() = default;

            BinaryTree<T>() = default;

            BinaryTree<T>(BinaryTree<T> &&o) noexcept {
                this->root = std::move(o.root);
            }

            BinaryTree<T>(const BinaryTree<T> &o) noexcept {
                if (o.root) {
                    this->add_root(*(o.root->val));
                    _copy(this->root, o.root);
                }
            }

            /// Inner deep copy function.
            /// \param to To Node
            /// \param from From Node
            void _copy(std::shared_ptr <Node> to, const std::shared_ptr <Node> from) {
                if (from->left) {
                    to->set_left(to, *(from->left->val));
                    _copy(to->left, from->left);
                }
                if (from->right) {
                    to->set_right(to, *(from->right->val));
                    _copy(to->right, from->right);
                }
            }

            /// Copy assigment operator.
            /// \param o source
            /// \return this.
            BinaryTree<T> &operator=(const BinaryTree<T> &o) {
                if (o.root) {
                    this->add_root(*(o.root->val));
                    _copy(this->root, o.root);
                }
                return *this;
            }

            /// Move operator.
            /// \param other source to take over.
            /// \return this.
            BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept {
                if (other.root) {
                    this->root = std::move(other.root);
                }
                return *this;
            }

            ///////////// Iterator /////////////
            class iterator : public std::iterator<std::forward_iterator_tag, T> {
                static int id;

                std::shared_ptr <Node> next;
                TraverseType traverse_type;
                int traverse_id;
                int distance;

                // Goes to deeper left most or right most child.
                void deepen_post_order() {
                    while (next->left || next->right) {
                        if (next->left) {
                            next = next->left;
                        } else if (next->right) {
                            next = next->right;
                        }
                    }
                }

                // Goes to deepest left child.
                void deepen_in_order() {
                    while (next->left) {
                        next = next->left;
                    }
                }

                public:
                    iterator(std::shared_ptr <Node> _root, TraverseType _traverse_type) : next(_root),
                                                                                          traverse_type(_traverse_type),
                                                                                          traverse_id(id),
                                                                                          distance(0) {
                        id++; // Iterator counter ++.

                        if (this->next) {
                            if (this->traverse_type == TraverseType::InOrder) {
                                this->deepen_in_order();
                            } else if (this->traverse_type == TraverseType::PostOrder) {
                                this->deepen_post_order();
                            } else if (this->traverse_type == TraverseType::PreOrder) {}
                            else {
                                throw std::runtime_error("Unknown traverse type");
                            }
                            next->visit_id = this->traverse_id;
                        }
                    }

                    std::shared_ptr <Node> &get_node_parent_sptr() {
                        return this->next;
                    }

                    T &operator*() const {
                        return *next->val;
                    }

                    T *operator->() const {
                        return &(*(next->val));
                    }

                    // Performs in order iteration
                    iterator &next_in_order() {
                        if (next->right) {
                            next = next->right;
                            // Go to left most
                            this->deepen_in_order();
                            return *this;
                        }

                        while (true) {
                            auto parent_spt = next->parent.lock();

                            // Traverse up by parent
                            if (!parent_spt) {
                                next.reset();
                                return *this;
                            }
                            if (parent_spt->left == next) {
                                next = parent_spt;
                                return *this;
                            }
                            next = parent_spt;
                        }
                    }


                    // Performs post order iteration.
                    iterator &next_post_order() {
                        auto parent_spt = next->parent.lock();

                        if (!parent_spt || parent_spt->right == next) {
                            next = parent_spt;
                        } else if (parent_spt->left == next) { // if im left child
                            // if i have a brother
                            if (parent_spt->right) {
                                next = parent_spt->right;
                                this->deepen_post_order();
                            } else {
                                next = parent_spt;
                            }
                        }

                        return *this;
                    }

                    // Performs pre order iteration.
                    iterator &next_pre_order() {
                        bool done = false;
                        while (!done && next) {
                            // If has a non visited left child.
                            if (next->left && !(next->left->visit_id == this->traverse_id)) {
                                next = next->left;
                                distance++;
                                done = true;
                            } else if (next->right && !(next->right->visit_id == this->traverse_id)) {
                                // Non vivisted right child.
                                next = next->right;
                                distance++;
                                done = true;
                            } else {
                                // Traverse up.
                                auto parent_spt = next->parent.lock();
                                next = parent_spt;
                                distance--;
                            }
                        }

                        if (next) {
                            // Set as visited.
                            next->visit_id = this->traverse_id;
                        }
                        return *this;
                    }


                    // ++i;
                    iterator &operator++() {
                        if (!next) {
                            throw std::runtime_error("iterator is done.");
                        }

                        switch (this->traverse_type) {
                            case TraverseType::InOrder:
                                return this->next_in_order();
                            case TraverseType::PreOrder:
                                return this->next_pre_order();
                            case TraverseType::PostOrder:
                                return this->next_post_order();
                            default:
                                return *this;
                        }
                    }

                    // i++;
                    // Usually iterators are passed by value and not by const& as they are small.
                    iterator operator++(int) {
                        iterator tmp = *this;
                        this->operator++();
                        return tmp;
                    }

                    bool operator==(const iterator &rhs) const {
                        return next == rhs.next || (!next && !rhs.next);
                    }

                    bool operator!=(const iterator &rhs) const {
                        return !operator==(rhs);
                    }

                    bool operator<(const iterator &o) const {
                        return *(next->val) < *(o->val);
                    }
            };


            ///////////// BinaryTree /////////////
            iterator begin() const{
                return this->begin_inorder();
            }

            iterator end() const{
                return this->end_inorder();
            }

            iterator begin_postorder() const{
                return iterator(root, TraverseType::PostOrder);
            }

            iterator begin_preorder() const{
                return iterator(root, TraverseType::PreOrder);
            }

            iterator begin_inorder() const {
                return iterator(root, TraverseType::InOrder);
            }

            iterator end_preorder() const{
                return iterator(nullptr, TraverseType::PreOrder);
            }

            iterator end_inorder() const{
                return iterator(nullptr, TraverseType::InOrder);
            }

            iterator end_postorder() const {
                return iterator(nullptr, TraverseType::PostOrder);
            }

            BinaryTree &add_left(const T &existing, const T &new_child_val) {
                return this->_add(existing, new_child_val, true);
            }

            BinaryTree &add_right(const T &existing, const T &new_child_val) {
                return this->_add(existing, new_child_val, false);
            }

            BinaryTree &add_root(T _val) {
                if (!root) {
                    root = std::shared_ptr<Node>(new Node());
                }

                root->val = std::make_unique<T>(_val);
                return *this;
            }

    };

    template<class T> inline std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& b){
        auto it = b.begin_preorder();
        while(it != b.end_preorder()){
            out << *it << " ";
            ++it;
        }
        return out;
    }

    // Maybe move to cpp file
    template<typename T>
    int BinaryTree<T>::iterator::id = 0;
}


#endif //BINARYTREE_B_BINARYTREE_HPP
