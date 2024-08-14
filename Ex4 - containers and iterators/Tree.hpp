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

        // Pre-order iterator class: current , left, right
        class PreOrderIterator
        {
        private:
            Node<T> *currentNode;
            stack<Node<T> *> nodeStack;

        public:
            PreOrderIterator(Node<T> *root = nullptr) : currentNode(root)
            {
                if (currentNode)
                {
                    nodeStack.push(currentNode);
                }
            }

            T &operator*()
            {
                return currentNode->value;
            }

            Node<T> *operator->()
            {
                return currentNode;
            }

            // Prefix increment
            PreOrderIterator &operator++()
            {
                if (!nodeStack.empty())
                {
                    currentNode = nodeStack.top();
                    nodeStack.pop();

                    // Push children in reverse order to the stack
                    for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it)
                    {
                        nodeStack.push(*it);
                    }

                    if (!nodeStack.empty())
                    {
                        currentNode = nodeStack.top();
                    }
                    else
                    {
                        currentNode = nullptr;
                    }
                }
                else
                {
                    currentNode = nullptr;
                }

                return *this;
            }

            // Postfix increment
            PreOrderIterator operator++(int)
            {
                PreOrderIterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const PreOrderIterator &other) const
            {
                return currentNode == other.currentNode;
            }

            bool operator!=(const PreOrderIterator &other) const
            {
                return !(*this == other);
            }
        };

    public:
        // Return an iterator to the beginning of the tree (pre-order)
        PreOrderIterator begin_pre_order()
        {
            return PreOrderIterator(root);
        }

        // Return an iterator to the end of the tree (pre-order)
        PreOrderIterator end_pre_order()
        {
            return PreOrderIterator(nullptr);
        }

        class PostOrderIterator
        {
        private:
            Node<T> *currentNode;
            std::stack<Node<T> *> nodeStack;
            std::stack<Node<T> *> visitedStack;

            void advanceToNext()
            {
                while (!nodeStack.empty())
                {
                    Node<T> *topNode = nodeStack.top();

                    // Check if all children have been visited or the node itself has already been processed
                    if (!topNode->children.empty() && (visitedStack.empty() || visitedStack.top() != topNode))
                    {
                        // Push children onto the stack in reverse order
                        visitedStack.push(topNode);
                        for (auto it = topNode->children.rbegin(); it != topNode->children.rend(); ++it)
                        {
                            if (*it)
                            {
                                nodeStack.push(*it);
                            }
                        }
                    }
                    else
                    {
                        nodeStack.pop();
                        currentNode = topNode;
                        return;
                    }
                }

                currentNode = nullptr; // End of traversal
            }

        public:
            PostOrderIterator(Node<T> *root = nullptr) : currentNode(nullptr)
            {
                if (root)
                {
                    nodeStack.push(root);
                    advanceToNext(); // Move to the first post-order node
                }
            }

            T &operator*()
            {
                return currentNode->value;
            }

            Node<T> *operator->()
            {
                return currentNode;
            }

            PostOrderIterator &operator++()
            {
                advanceToNext();
                return *this;
            }

            PostOrderIterator operator++(int)
            {
                PostOrderIterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const PostOrderIterator &other) const
            {
                return currentNode == other.currentNode;
            }

            bool operator!=(const PostOrderIterator &other) const
            {
                return currentNode != other.currentNode;
            }
        };

    public:
        // Return an iterator to the beginning of the tree (post-order)
        PostOrderIterator begin_post_order()
        {
            return PostOrderIterator(root);
        }

        // Return an iterator to the end of the tree (post-order)
        PostOrderIterator end_post_order()
        {
            return PostOrderIterator(nullptr);
        }
    };
}

#endif
