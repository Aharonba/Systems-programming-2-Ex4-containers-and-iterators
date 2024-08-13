#ifndef TREE_HPP
#define TREE_HPP

#include <stdexcept>
#include <stack>
#include <queue>
using namespace std;
#include <SFML/Graphics.hpp> // Add SFML Graphics header
#include "Node.hpp"

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
            cout << string(depth * 2, ' ') << node->value << endl;

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
    };

}

#endif
