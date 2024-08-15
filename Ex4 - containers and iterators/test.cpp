#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include "TreeIterators.hpp"

using namespace ariel;

TEST_CASE("Binary Tree Functionality with Doubles")
{
    /**
     *       root = 10.5
     *     /       \
     *    20.3     30.2
     *   /  \      /  \
     *  15.4 5.1  25.6 35.7
     */

    // Set up the tree with a different structure
    Node<double> root_node(10.5);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(&root_node);
    Node<double> n1(20.3);
    Node<double> n2(30.2);
    Node<double> n3(15.4);
    Node<double> n4(5.1);
    Node<double> n5(25.6);
    Node<double> n6(35.7);

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);
    tree.add_sub_node(&n2, &n6);

    SUBCASE("Pre-Order Traversal")
    {
        std::vector<double> expected = {10.5, 20.3, 15.4, 5.1, 30.2, 25.6, 35.7};
        auto it = tree.begin_pre_order();
        for (double value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("In-Order Traversal")
    {
        std::vector<double> expected = {15.4, 20.3, 5.1, 10.5, 25.6, 30.2, 35.7}; 
        auto it = tree.begin_in_order();
        for (double value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("Post-Order Traversal")
    {
        std::vector<double> expected = {15.4, 5.1, 20.3, 25.6, 35.7, 30.2, 10.5};
        auto it = tree.begin_post_order();
        for (double value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("BFS Traversal")
    {
        std::vector<double> expected = {10.5, 20.3, 30.2, 15.4, 5.1, 25.6, 35.7};
        auto it = tree.begin_bfs_scan();
        for (double value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("DFS Traversal")
    {
        std::vector<double> expected = {10.5, 20.3, 15.4, 5.1, 30.2, 25.6, 35.7};
        auto it = tree.begin_dfs_scan();
        for (double value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("Heap Conversion")
    {
        Node<double> root_node(10.5);
        Tree<double> heapTree; // Binary tree that contains doubles.
        heapTree.add_root(&root_node);
        Node<double> n1(20.3);
        Node<double> n2(30.2);
        Node<double> n3(15.4);
        Node<double> n4(5.1);
        Node<double> n5(25.6);
        Node<double> n6(35.7);

        heapTree.add_sub_node(&root_node, &n1);
        heapTree.add_sub_node(&root_node, &n2);
        heapTree.add_sub_node(&n1, &n3);
        heapTree.add_sub_node(&n1, &n4);
        heapTree.add_sub_node(&n2, &n5);
        heapTree.add_sub_node(&n2, &n6);

        auto heapIt = heapTree.myHeap();
        std::vector<double> expectedHeap = {5.1, 10.5, 25.6, 15.4, 20.3, 30.2, 35.7}; // Check if heap conversion is correct
        for (double value : expectedHeap)
        {
            CHECK(*heapIt == value);
            ++heapIt;
        }
    }
}

TEST_CASE("Binary Tree Functionality with chars")
{
    /**
     *       root = a
     *     /       \
     *    f         r
     *   /  \      /  \
     *  a    c    g     b
     */

    // Set up the tree with a different structure
    Node<char> root_node('a');
    Tree<char> tree; // Binary tree that contains doubles.
    tree.add_root(&root_node);
    Node<char> n1('f');
    Node<char> n2('r');
    Node<char> n3('a');
    Node<char> n4('c');
    Node<char> n5('g');
    Node<char> n6('b');

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);
    tree.add_sub_node(&n2, &n6);

    SUBCASE("Pre-Order Traversal")
    {
        std::vector<char> expected = {'a', 'f', 'a', 'c', 'r', 'g', 'b'};
        auto it = tree.begin_pre_order();
        for (char value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("In-Order Traversal")
    {
        std::vector<char> expected = {'a', 'f', 'c', 'a', 'g', 'r', 'b'};
        auto it = tree.begin_in_order();
        for (char value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("Post-Order Traversal")
    {
        std::vector<char> expected = {'a', 'c', 'f', 'g', 'b', 'r', 'a'};
        auto it = tree.begin_post_order();
        for (char value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("BFS Traversal")
    {
        std::vector<char> expected = {'a', 'f', 'r', 'a', 'c', 'g', 'b'};
        auto it = tree.begin_bfs_scan();
        for (char value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("DFS Traversal")
    {
        std::vector<char> expected = {'a', 'f', 'a', 'c', 'r', 'g', 'b'};
        auto it = tree.begin_dfs_scan();
        for (char value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("Heap Conversion")
    {
        Node<char> root_node('a');
        Tree<char> heapTree; // Binary tree that contains doubles.
        heapTree.add_root(&root_node);
        Node<char> n1('f');
        Node<char> n2('r');
        Node<char> n3('a');
        Node<char> n4('c');
        Node<char> n5('g');
        Node<char> n6('b');

        heapTree.add_sub_node(&root_node, &n1);
        heapTree.add_sub_node(&root_node, &n2);
        heapTree.add_sub_node(&n1, &n3);
        heapTree.add_sub_node(&n1, &n4);
        heapTree.add_sub_node(&n2, &n5);
        heapTree.add_sub_node(&n2, &n6);

        auto heapIt = heapTree.myHeap();
        std::vector<double> expectedHeap = {'a', 'a', 'b', 'f', 'c', 'g', 'r'}; // Check if heap conversion is correct
        for (double value : expectedHeap)
        {
            CHECK(*heapIt == value);
            ++heapIt;
        }
    }
}

TEST_CASE("3'son Tree Functionality")
{
    /**
     *       root = 10
     *     /    |    \
     *    5     7    15
     *   /|\   /|\   /|\
     *  1 2 3 8 9 10 20 25 30
     */

    Tree<int, 3> tree; 
    // Create nodes
    Node<int> *root = new Node<int>(10);
    Node<int> *leftChild = new Node<int>(5);
    Node<int> *middleChild = new Node<int>(7);
    Node<int> *rightChild = new Node<int>(15);

    Node<int> *leftChild1 = new Node<int>(1);
    Node<int> *leftChild2 = new Node<int>(2);
    Node<int> *leftChild3 = new Node<int>(3);

    Node<int> *middleChild1 = new Node<int>(8);
    Node<int> *middleChild2 = new Node<int>(9);
    Node<int> *middleChild3 = new Node<int>(10);

    Node<int> *rightChild1 = new Node<int>(20);
    Node<int> *rightChild2 = new Node<int>(25);
    Node<int> *rightChild3 = new Node<int>(30);

    // Build the tree
    tree.add_root(root);
    tree.add_sub_node(root, leftChild);
    tree.add_sub_node(root, middleChild);
    tree.add_sub_node(root, rightChild);

    tree.add_sub_node(leftChild, leftChild1);
    tree.add_sub_node(leftChild, leftChild2);
    tree.add_sub_node(leftChild, leftChild3);

    tree.add_sub_node(middleChild, middleChild1);
    tree.add_sub_node(middleChild, middleChild2);
    tree.add_sub_node(middleChild, middleChild3);

    tree.add_sub_node(rightChild, rightChild1);
    tree.add_sub_node(rightChild, rightChild2);
    tree.add_sub_node(rightChild, rightChild3);

    SUBCASE("Root and Children")
    {
        CHECK(tree.get_root()->get_value() == 10);
        CHECK(root->children[0]->get_value() == 5);
        CHECK(root->children[1]->get_value() == 7);
        CHECK(root->children[2]->get_value() == 15);

        CHECK(leftChild->children[0]->get_value() == 1);
        CHECK(leftChild->children[1]->get_value() == 2);
        CHECK(leftChild->children[2]->get_value() == 3);

        CHECK(middleChild->children[0]->get_value() == 8);
        CHECK(middleChild->children[1]->get_value() == 9);
        CHECK(middleChild->children[2]->get_value() == 10);

        CHECK(rightChild->children[0]->get_value() == 20);
        CHECK(rightChild->children[1]->get_value() == 25);
        CHECK(rightChild->children[2]->get_value() == 30);
    }

    SUBCASE("Pre-Order Traversal")
    {
        std::vector<int> expected = {10, 5, 1, 2, 3, 7, 8, 9, 10, 15, 20, 25, 30};
        auto it = tree.begin_pre_order();
        for (int value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("In-Order Traversal")
    {
        std::vector<int> expected = {10, 5, 1, 2, 3, 7, 8, 9, 10, 15, 20, 25, 30};
        auto it = tree.begin_in_order();
        for (int value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("BFS Traversal")
    {
        std::vector<int> expected = {10, 5, 7, 15, 1, 2, 3, 8, 9, 10, 20, 25, 30};
        auto it = tree.begin_bfs_scan();
        for (int value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    SUBCASE("DFS Traversal")
    {
        std::vector<int> expected = {10, 5, 1, 2, 3, 7, 8, 9, 10, 15, 20, 25, 30};
        auto it = tree.begin_dfs_scan();
        for (int value : expected)
        {
            CHECK(*it == value);
            ++it;
        }
    }

    // Cleanup
    delete root;
    delete leftChild;
    delete middleChild;
    delete rightChild;
    delete leftChild1;
    delete leftChild2;
    delete leftChild3;
    delete middleChild1;
    delete middleChild2;
    delete middleChild3;
    delete rightChild1;
    delete rightChild2;
    delete rightChild3;
}
