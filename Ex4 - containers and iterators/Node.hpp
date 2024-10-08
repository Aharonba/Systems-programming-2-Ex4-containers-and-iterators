/**
 * Name: Aharon bassous
 * Email: Aharonba123@gmail.com
 */


#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

namespace ariel
{
    template <typename T>
    class Node
    {
    public:
        T value;                         // The value stored in the node
        std::vector<Node<T> *> children; // Vector of pointers to child nodes

        Node(const T &val) : value(val) {}

        void add_child(Node<T> *child)
        {
            children.push_back(child);
        }

        T& get_value()  
        {
            return value;
        }
    };
};
#endif
