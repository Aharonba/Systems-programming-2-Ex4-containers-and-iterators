#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include <stack>
#include "Node.hpp"
#include <unordered_set>

using namespace std;

namespace ariel
{
    // Pre-order iterator class: current , left, right
    template <typename T, size_t K = 2>
    class PreOrderIterator
    {
    private:
        Node<T> *currentNode;
        std::stack<Node<T> *> nodeStack;

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

    template <typename T>
    class PostOrderIterator
    {
    private:
        Node<T> *current;
        std::stack<Node<T> *> stk;
        std::unordered_set<Node<T> *> visited;

        void push_children(Node<T> *node)
        {
            if (node)
            {
                stk.push(node);
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
                {
                    if (*it)
                        stk.push(*it);
                }
            }
        }

        void advance()
        {
            while (!stk.empty())
            {
                Node<T> *node = stk.top(); // Get the current node
                if (node == nullptr)
                {
                    stk.pop(); // Remove the null marker indicating a return to a parent node.
                    if (!stk.empty())
                    {
                        current = stk.top(); // Set the current node to the next node in the stack.
                        stk.pop();           // Remove the current node from the stack.
                    }
                    return;
                }
                if (visited.find(node) == visited.end())
                {                         // If the node hasn't been visited yet.
                    stk.push(nullptr);    // Push a null marker to indicate a return to this node.
                    push_children(node);  // Push the children of the node onto the stack.
                    visited.insert(node); // Mark the node as visited.
                }
                else
                {
                    stk.pop(); // Remove the node from the stack if it has been visited.
                }
            }
            current = nullptr; // No more nodes to visit.
        }

    public:
        PostOrderIterator(Node<T> *root = nullptr) : current(nullptr)
        {
            if (root)
            {
                push_children(root);
                advance(); // Move to the first post-order node
            }
        }

        T &operator*() const
        {
            return current->get_value();
        }

        Node<T> *operator->() const
        {
            return current;
        }

        PostOrderIterator &operator++()
        {
            advance();
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
            return current == other.current;
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !(*this == other);
        }
    };

    template <typename T>
    class InOrderIterator
    {
    private:
        Node<T> *current;                      // Pointer to the current node in the iteration.
        std::stack<Node<T> *> stk;             // Stack to manage nodes for traversal.
        std::unordered_set<Node<T> *> visited; // Set to track visited nodes in DFS.
        bool isBinary;                         // Flag to determine if the tree is binary or general.

        // Helper function to push all left nodes of a binary tree onto the stack.
        void push_left(Node<T> *node)
        {
            while (node)
            {
                stk.push(node); // Push the current node onto the stack.
                // Move to the left child. In binary trees, left is the first child.
                node = node->children.size() > 0 ? node->children[0] : nullptr;
            }
        }

    public:
        // Constructor to initialize the iterator.
        InOrderIterator(Node<T> *root, bool binary) : current(nullptr), isBinary(binary)
        {
            if (isBinary)
            {
                push_left(root); // For binary trees, push all left nodes starting from the root.
            }
            else
            {
                if (root)
                    stk.push(root); // For general trees, just push the root node.
            }
            advance(); // Move to the first valid node in the iteration.
        }

        // Function to advance the iterator to the next node.
        void advance()
        {
            if (isBinary)
            {
                // Handling binary trees:
                if (!stk.empty())
                {
                    current = stk.top(); // Get the top node from the stack.
                    stk.pop();           // Remove it from the stack.

                    // If there are more than one children, push the right child onto the stack.
                    if (current->children.size() > 1)
                    {
                        push_left(current->children[1]); // Push the right child and its descendants.
                    }
                }
                else
                {
                    current = nullptr; // No more nodes to visit.
                }
            }
            else
            {
                // Handling general trees (DFS):
                while (!stk.empty())
                {
                    current = stk.top(); // Get the top node from the stack.
                    stk.pop();           // Remove it from the stack.

                    if (visited.find(current) == visited.end())
                    {
                        // If the node has not been visited yet:
                        visited.insert(current); // Mark the node as visited.

                        // Push all children onto the stack in reverse order.
                        for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                        {
                            if (*it)
                                stk.push(*it);
                        }
                        break; // Exit the loop once the next node has been found.
                    }
                }
            }
        }

        // Dereference operator to access the value of the current node.
        T &operator*() const
        {
            return current->get_value(); // Assume get_value() is a method in Node<T>.
        }

        // Arrow operator to access the members of the current node.
        Node<T> *operator->() const
        {
            return current;
        }

        // Prefix increment operator to advance to the next node.
        InOrderIterator &operator++()
        {
            advance(); // Move to the next node in the in-order traversal.
            return *this;
        }

        // Comparison operator to check if two iterators are different.
        bool operator!=(const InOrderIterator &other) const
        {
            return current != other.current; // Compare the current nodes.
        }
    };

    template <typename T>
    class BFSIterator
    {
    private:
        Node<T> *current;        // Current node in the BFS traversal
        std::queue<Node<T> *> q; // Queue to manage nodes for BFS

    public:
        BFSIterator(Node<T> *root = nullptr) : current(nullptr)
        {
            if (root)
            {
                q.push(root); // Start BFS from the root node
                advance();    // Move to the first valid node
            }
        }

        void advance()
        {
            if (!q.empty())
            {
                current = q.front(); // Get the front node from the queue
                q.pop();             // Remove it from the queue

                // Enqueue all children of the current node
                for (auto child : current->children)
                {
                    if (child)
                        q.push(child);
                }
            }
            else
            {
                current = nullptr; // No more nodes to visit
            }
        }

        T &operator*() const
        {
            return current->get_value(); // Access the value of the current node
        }

        Node<T> *operator->() const
        {
            return current; // Access the members of the current node
        }

        BFSIterator &operator++()
        {
            advance(); // Move to the next node in the BFS traversal
            return *this;
        }

        BFSIterator operator++(int)
        {
            BFSIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const BFSIterator &other) const
        {
            return current == other.current; // Compare current nodes
        }

        bool operator!=(const BFSIterator &other) const
        {
            return !(*this == other); // Check for inequality
        }
    };

    template <typename T>
    class DFSIterator
    {
    private:
        Node<T> *current;                      // Pointer to the current node in the DFS traversal
        std::stack<Node<T> *> stk;             // Stack to manage nodes for DFS
        std::unordered_set<Node<T> *> visited; // Set to track visited nodes

    public:
        // Constructor initializes the iterator
        DFSIterator(Node<T> *root = nullptr) : current(nullptr)
        {
            if (root)
            {
                stk.push(root); // Start DFS from the root node
                advance();      // Move to the first valid node
            }
        }

        // Function to advance the iterator to the next node
        void advance()
        {
            while (!stk.empty())
            {
                current = stk.top(); // Get the top node from the stack
                stk.pop();           // Remove it from the stack

                if (visited.find(current) == visited.end())
                {
                    // If the node has not been visited yet
                    visited.insert(current); // Mark the node as visited

                    // Push all children onto the stack in reverse order
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                    {
                        if (*it)
                            stk.push(*it);
                    }
                    return; // Exit once the next node has been found
                }
            }
            current = nullptr; // No more nodes to visit
        }

        // Dereference operator to access the value of the current node
        T &operator*() const
        {
            return current->get_value(); // Assume get_value() is a method in Node<T>
        }

        // Arrow operator to access the members of the current node
        Node<T> *operator->() const
        {
            return current;
        }

        // Prefix increment operator to advance to the next node
        DFSIterator &operator++()
        {
            advance(); // Move to the next node in the DFS traversal
            return *this;
        }

        // Postfix increment operator to advance to the next node
        DFSIterator operator++(int)
        {
            DFSIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Comparison operator to check if two iterators are equal
        bool operator==(const DFSIterator &other) const
        {
            return current == other.current;
        }

        // Comparison operator to check if two iterators are different
        bool operator!=(const DFSIterator &other) const
        {
            return !(*this == other);
        }
    };

} // namespace ariel

#endif
