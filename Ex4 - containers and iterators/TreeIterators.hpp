#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include <stack>
#include "Node.hpp"
#include <unordered_set>

using namespace std;

namespace ariel
{

    ///// Pre-order iterator class: current, left, right ///////

    template <typename T>
    class PreOrderIterator
    {
    private:
        Node<T> *currentNode;
        std::stack<Node<T> *> nodeStack; // Stack to manage the traversal of nodes
        bool isBinary;                   // Flag to determine if the tree is binary or general

    public:
        // Constructor initializes the iterator at the root node
        PreOrderIterator(Node<T> *root = nullptr, bool binary = false) : currentNode(root), isBinary(binary)
        {
            if (currentNode)
            {
                nodeStack.push(currentNode); // Start traversal from the root
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

        // Prefix increment: moves to the next node in pre-order
        PreOrderIterator &operator++()
        {
            if (!nodeStack.empty())
            {
                currentNode = nodeStack.top();
                nodeStack.pop();

                if (isBinary)
                {
                    // If the tree is binary, push the right child first, then the left child
                    if (currentNode->children.size() > 1)
                    {
                        nodeStack.push(currentNode->children[1]);
                    }
                    if (currentNode->children.size() > 0)
                    {
                        nodeStack.push(currentNode->children[0]);
                    }
                }
                else
                {
                    // For general trees, push children in reverse order to the stack to maintain left-to-right processing
                    for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it)
                    {
                        nodeStack.push(*it);
                    }
                }

                // Update currentNode to the next node in the stack
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
                currentNode = nullptr; // End of traversal
            }

            return *this;
        }

        // Postfix increment: creates a copy before advancing
        PreOrderIterator operator++(int)
        {
            PreOrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality operator: checks if two iterators are at the same node
        bool operator==(const PreOrderIterator &other) const
        {
            return currentNode == other.currentNode;
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !(*this == other);
        }
    };

    ///// Post-order iterator class: left, right, current ///////
    template <typename T>
    class PostOrderIterator
    {
    private:
        Node<T> *current;
        std::stack<Node<T> *> stk;             // Stack to manage the traversal of nodes
        std::unordered_set<Node<T> *> visited; // Set to track visited nodes
        bool isBinary;                         // Flag to determine if the tree is binary or general

        // Helper function to push children of a node onto the stack in reverse order
        void push_children(Node<T> *node)
        {
            if (node)
            {
                stk.push(node);
                if (isBinary)
                {
                    // For binary trees, push right child first, then left child
                    if (node->children.size() > 1)
                    {
                        stk.push(node->children[1]); // Push right child
                    }
                    if (node->children.size() > 0)
                    {
                        stk.push(node->children[0]); // Push left child
                    }
                }
                else
                {
                    // For general trees, push children in reverse order
                    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
                    {
                        if (*it)
                            stk.push(*it);
                    }
                }
            }
        }

        // Advance to the next node in the post-order traversal
        void advance()
        {
            // Continue processing nodes while there are nodes in the stack
            while (!stk.empty())
            {
                // Retrieve the node at the top of the stack
                Node<T> *node = stk.top();

                // Handle the null marker (indicates completion of child processing)
                if (node == nullptr)
                {
                    stk.pop(); // Remove the null marker from the stack
                    if (!stk.empty())
                    {
                        current = stk.top(); // Set the current node to the next node in the stack
                        stk.pop();           // Remove that node from the stack, as it's now the current node
                    }
                    return; // Exit the function since we have found the next node in the traversal
                }

                // Check if the node has been visited
                if (visited.find(node) == visited.end())
                {
                    stk.push(nullptr);    // Push a null marker onto the stack to mark this node for post-visit
                    push_children(node);  // Push the node's children onto the stack (in reverse order for correct processing)
                    visited.insert(node); // Mark the node as visited
                }
                else
                {
                    stk.pop(); // If the node was already visited, pop it from the stack as its processing is complete
                }
            }

            // If the stack is empty, it means we've completed the traversal
            current = nullptr; // Set current to nullptr to indicate the end of the traversal
        }

    public:
        // Constructor initializes the iterator at the first post-order node
        PostOrderIterator(Node<T> *root = nullptr, bool binary = false) : current(nullptr), isBinary(binary)
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

        // Prefix increment: moves to the next node in post-order
        PostOrderIterator &operator++()
        {
            advance(); // Move to the next node in the post-order traversal
            return *this;
        }

        // Postfix increment: creates a copy before advancing
        PostOrderIterator operator++(int)
        {
            PostOrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality operator: checks if two iterators are at the same node
        bool operator==(const PostOrderIterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !(*this == other);
        }
    };

    ///// In-order iterator class: left, current, right ///////

    template <typename T>
    class InOrderIterator
    {
    private:
        Node<T> *current;
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

    ///// BFS iterator class (using queue): ///////

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

    ///// DFS iterator class (using stack): ///////

    template <typename T>
    class DFSIterator
    {
    private:
        Node<T> *current;
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

    template <typename T>
    class HeapIterator
    {
    private:
        Node<T> *current;
        std::queue<Node<T> *> nodeQueue; // Queue to hold nodes for level-order traversal

    public:
        // Constructor initializes the iterator at the root node
        HeapIterator(Node<T> *root = nullptr) : current(root)
        {
            if (current)
            {
                nodeQueue.push(current); // Start with the root node
            }
        }

        // Dereference operator returns the current node's value
        T &operator*()
        {
            return current->value;
        }

        // Arrow operator returns the current node
        Node<T> *operator->()
        {
            return current;
        }

        // Prefix increment moves to the next node in level-order
        HeapIterator &operator++()
        {
            if (!nodeQueue.empty())
            {
                current = nodeQueue.front();
                nodeQueue.pop();

                // Push the left and right children of the current node into the queue
                if (current->children.size() > 0 && current->children[0])
                {
                    nodeQueue.push(current->children[0]);
                }
                if (current->children.size() > 1 && current->children[1])
                {
                    nodeQueue.push(current->children[1]);
                }

                // Update current to the next node in the queue
                if (!nodeQueue.empty())
                {
                    current = nodeQueue.front();
                }
                else
                {
                    current = nullptr; // End of traversal
                }
            }
            else
            {
                current = nullptr; // End of traversal
            }

            return *this;
        }

        // Postfix increment creates a copy before advancing
        HeapIterator operator++(int)
        {
            HeapIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality operator checks if two iterators are at the same node
        bool operator==(const HeapIterator &other) const
        {
            return current == other.current;
        }

        // Inequality operator checks if two iterators are not at the same node
        bool operator!=(const HeapIterator &other) const
        {
            return !(*this == other);
        }
    };
} // namespace ariel

#endif
