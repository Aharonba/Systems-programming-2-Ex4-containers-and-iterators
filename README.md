Here's a detailed README for your project:

---

# Tree Visualization Project

## Overview

This project implements a tree structure with various traversal methods and includes a visualization using SFML (Simple and Fast Multimedia Library). The project is implemented in C++ and is designed to demonstrate different types of tree traversals, as well as the functionality of transforming a binary tree into a minimum heap.

## Files

### 1. **Node.hpp**
   - **Description**: Defines the `Node` class template, which represents a node in the tree. Each node holds a value and pointers to its children.
   - **Key Components**:
     - **Attributes**: 
       - `T value`: The value stored in the node.
       - `std::vector<Node<T>*> children`: A vector of pointers to the node's children.
     - **Methods**:
       - `T get_value()`: Returns the value of the node.
       - `void add_child(Node<T>* child)`: Adds a child to the node.

### 2. **Tree.hpp**
   - **Description**: Defines the `Tree` class template, which represents the tree itself. The class allows adding nodes and performing various tree traversals.
   - **Key Components**:
     - **Attributes**:
       - `Node<T>* root`: Pointer to the root node of the tree.
       - `int k`: Maximum number of children per node (only used for k-ary trees).
       - `bool isBinary`: Indicates if the tree is binary.
     - **Methods**:
       - `void add_root(Node<T>* root_node)`: Sets the root of the tree.
       - `void add_sub_node(Node<T>* parent, Node<T>* child)`: Adds a child node to the specified parent node.
       - Traversal methods like `begin_pre_order()`, `begin_in_order()`, `begin_post_order()`, `begin_bfs_scan()`, `begin_dfs_scan()`.
       - `HeapIterator<T> myHeap()`: Transforms the binary tree into a minimum heap and returns an iterator over the heap.

### 3. **TreeIterators.hpp**
   - **Description**: Contains the implementation of various iterators for the `Tree` class. These iterators allow traversing the tree in different orders, such as pre-order, in-order, post-order, BFS, and DFS.
   - **Key Components**:
     - **Classes**:
       - `PreOrderIterator<T>`
       - `InOrderIterator<T>`
       - `PostOrderIterator<T>`
       - `BFSIterator<T>`
       - `DFSIterator<T>`
       - `HeapIterator<T>`

### 4. **Demo.cpp**
   - **Description**: Demonstrates the functionality of the `Tree` class using a binary tree with nodes containing `double` values. The demo visually represents the tree using SFML.
   - **Key Components**:
     - **Setup**: Initializes the SFML window and sets up the tree structure.
     - **Visualization**: Uses SFML to draw the tree and its nodes on the screen.

### 5. **test.cpp**
   - **Description**: Contains test cases using the Doctest framework to verify the correctness of the `Tree` and `Node` classes. It tests different tree structures, traversal methods, and heap conversion.
   - **Key Test Cases**:
     - **Basic Tree Functionality**: Tests root and children relationships.
     - **Traversal Tests**: Verifies the output of pre-order, in-order, post-order, BFS, and DFS traversals.
     - **Heap Conversion Test**: Checks if the tree is correctly converted into a minimum heap.

### 6. **Makefile**
   - **Description**: Automates the compilation of the project. It includes targets for building the demo executable, running tests, and cleaning up build files.
   - **Targets**:
     - `all`: Builds the demo executable.
     - `test`: Builds the test executable.
     - `run`: Runs the demo executable.
     - `clean`: Removes all compiled files.

### 7. **sansation.ttf**
   - **Description**: A font file used in the SFML visualization to display text.

---

This README should cover all the files in your project and provide clear instructions on how to build and run the project.
