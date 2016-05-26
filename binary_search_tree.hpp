#pragma once

#include <stdexcept>
#include <iostream>

template<typename T, typename V>
struct TreeNode {
    TreeNode(T v, V other_data) : data(v), other_data(other_data) {}
    T data;
    V other_data;
    TreeNode* left_child;
    TreeNode* right_child;
};

template<typename T, typename V>
class Tree {
public:

    Tree():
        root_(nullptr)
    {

    }

    /*
        Free the memory.
    */
    ~Tree()
    {
        FreeTreeMemory(root_);
    }

    /*
        Recursive function to release memory from the tree.
    */
    void FreeTreeMemory(TreeNode<T,V>* root)
    {
        if (root) {
            // Get the children and free their subtree.
            TreeNode<T,V>* left_root = root->left_child;
            TreeNode<T,V>* right_root = root->right_child;

            delete root;

            // And delete subtrees.
            if (left_root) {
                FreeTreeMemory(left_root);
            }

            if (right_root) {
                FreeTreeMemory(right_root);
            }
        }
    }

    /*
        Insert data into the tree.
    */
    void InsertNode(T data, V other_data)
    {
        if (root_ == nullptr) {
            // First data to be inserted.
            root_ = new TreeNode<T,V>(data, other_data);
        } else {
            InsertChild(root_, data, other_data);
        }
    }

    /*
        Print tree. Depth-first search.
    */
    void PrintTree()
    {
        if (root_) {
            PrintSubtree(root_);
        } else {
            std::cout << "The tree is empty\n";
        }
    }

    TreeNode<T,V>* Search(T data)
    {
        return SearchChild(root_, data);
    }

private:
    /*
        Top of the tree
    */
    TreeNode<T,V>* root_;

    /*
        Insert node into a tree. It will compare the value with the given root
        and decide whether to put the data in the left tree or the right tree.
    */
    void InsertChild(TreeNode<T,V>* root, T data, V other_data)
    {
        if (root) {
            if (data > root->data) {
                // right subtree
                if (root->right_child) {
                    InsertChild(root->right_child, data, other_data);
                } else {
                    root->right_child = new TreeNode<T,V>(data, other_data);
                }
            } else {
                // left subtree
                if (root->left_child) {
                    InsertChild(root->left_child, data, other_data);
                } else {
                    root->left_child = new TreeNode<T,V>(data, other_data);
                }
            }
        } else {
            throw std::runtime_error("Root is nullptr...");
        }
    }

    /*
        Search node with given value. If does not exist, return nullptr.
    */
    TreeNode<T,V>* SearchChild(TreeNode<T,V>* root, T data)
    {
        if (root) {
            if (data > root->data) {
                return SearchChild(root->right_child, data);
            } else if (data < root->data) {
                return SearchChild(root->left_child, data);
            } else if (data == root->data) {
                return root;
            }
        }
        return nullptr;
    }

    /*
        Print the tree using pre-order traversal
    */
    void PrintSubtree(TreeNode<T,V>* root)
    {
        if (root) {
            std::cout << root->data << " ";

            if (root->left_child) {
                PrintSubtree(root->left_child);
            }

            if (root->right_child) {
                PrintSubtree(root->right_child);
            }
        }
    }
};
