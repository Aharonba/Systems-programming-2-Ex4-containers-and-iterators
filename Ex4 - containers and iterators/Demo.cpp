/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "TreeVisualizer.hpp" // Include the new TreeVisualizer header

using namespace ariel;
using namespace std;

int main()
{

    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(&root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "pre order: " << endl;
    // current -> left -> right
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "post order: " << endl;
    // left -> right -> current
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "in order: " << endl;
    // left -> current -> right
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "BFS: " << endl;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "Printing the tree structure: " << endl;

    tree.print();
    // } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    // Create the TreeVisualizer and display the tree
    TreeVisualizer<double> visualizer(tree);
    visualizer.display();

    // Tree<double, 3> three_ary_tree; // 3-ary tree.
    // three_ary_tree.add_root(&root_node);
    // three_ary_tree.add_sub_node(&root_node, &n1);
    // three_ary_tree.add_sub_node(&root_node, &n2);
    // three_ary_tree.add_sub_node(&root_node, &n3);
    // three_ary_tree.add_sub_node(&n1, &n4);
    // three_ary_tree.add_sub_node(&n2, &n5);


    // //  // The tree should look like:
    // // /**
    // //  *       root = 1.1
    // //  *     /      |     \
    // //  *    1.2    1.3    1.4
    // //  *   /        |
    // //  *  1.5      1.6
    // //  */

    // cout << "Printing the tree structure: " << endl;

    // three_ary_tree.print();

    // cout << "pre order: " << endl;
    // current -> left -> right
    // for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    // cout << "post order: " << endl;
    // // left -> right -> current
    // for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    // cout << "in order: " << endl;
    // // left -> current -> right
    // for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    // cout << "BFS: " << endl;

    // for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    // {
    //     cout << node->get_value() << endl;
    // } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
}