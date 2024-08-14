#ifndef TREE_HPP
#define TREE_HPP

#include <stdexcept>
#include <stack>
#include <queue>
#include <SFML/Graphics.hpp> // Add SFML Graphics header
#include <stdexcept>
#include "Node.hpp"
#include "TreeIterators.hpp"

using namespace std;

namespace ariel
{
    template <typename T, size_t K = 2>
    class Tree
    {
    private:
        Node<T> *root;

    public:
        Tree() : root(nullptr) {}

        void add_root(Node<T> *newRoot)
        {
            root = newRoot;
        }

        void add_sub_node(Node<T> *parent, Node<T> *son)
        {
            if (!parent)
                throw std::invalid_argument("Parent node cannot be null.");
            if (parent->children.size() >= K)
                throw std::overflow_error("Maximum number of children reached.");
            parent->add_child(son);
        }

        Node<T> *get_root() const
        {
            return root;
        }

        void print_tree(Node<T> *node, int depth)
        {
            if (!node)
                return;

            // Print the current node value with indentation based on depth
            std::cout << std::string(depth * 2, ' ') << node->value << std::endl;

            // Recursively print each child node
            for (auto child : node->children)
            {
                print_tree(child, depth + 1);
            }
        }

        // Print the entire tree
        void print()
        {
            print_tree(root, 0);
        }

        // Return an iterator to the beginning of the tree (pre-order)
        PreOrderIterator<T, K> begin_pre_order()
        {
            return PreOrderIterator<T, K>(root);
        }

        // Return an iterator to the end of the tree (pre-order)
        PreOrderIterator<T, K> end_pre_order()
        {
            return PreOrderIterator<T, K>(nullptr);
        }

        // Return an iterator to the beginning of the tree (post-order)
        PostOrderIterator<T> begin_post_order()
        {
            return PostOrderIterator<T>(root);
        }

        // Return an iterator to the end of the tree (post-order)
        PostOrderIterator<T> end_post_order()
        {
            return PostOrderIterator<T>(nullptr);
        }

        // Return an iterator to the beginning of the tree (in-order)
        InOrderIterator<T> begin_in_order()
        {
            return InOrderIterator<T>(root, K == 2);
        }

        // Return an iterator to the end of the tree (in-order)
        InOrderIterator<T> end_in_order()
        {
            return InOrderIterator<T>(nullptr, K == 2);
        }

        // Function to return a BFS iterator pointing to the beginning of the BFS scan
        BFSIterator<T> begin_bfs_scan()
        {
            return BFSIterator<T>(root); // Create BFSIterator starting at root
        }

        // Function to return a BFS iterator pointing to the end of the BFS scan
        BFSIterator<T> end_bfs_scan()
        {
            return BFSIterator<T>(nullptr); // Create BFSIterator with a nullptr indicating the end
        }

        // Begin iterator for DFS scan
        DFSIterator<T> begin_dfs_scan()
        {
            return DFSIterator<T>(root); // Start DFS from the root node
        }

        // End iterator for DFS scan
        DFSIterator<T> end_dfs_scan()
        {
            return DFSIterator<T>(nullptr); // End DFS with a nullptr indicating no more nodes
        }
    };
}

#endif
