# B-Tree Implementation in C

## Introduction
This repository contains an implementation of a **B-Tree** in C, a self-balancing search tree commonly used in databases and file systems. The implementation supports **insertion**, **splitting of nodes**, and **in-order traversal** of the tree.

## Features
- Implementation of a **B-tree** with configurable order (M).
- Supports **insertion** of elements while maintaining the tree balance.
- Handles **node splitting** when a node exceeds its key capacity.
- Includes an **in-order traversal** function for displaying elements in sorted order.

## Table of Contents
- [B-tree Overview](#b-tree-overview)
- [Code Structure](#code-structure)
- [Functions Explained](#functions-explained)
- [Compilation and Execution](#compilation-and-execution)
- [Example Usage](#example-usage)
- [Potential Issues](#potential-issues)
- [References](#references)

## B-tree Overview
A **B-tree** is a self-balancing search tree in which each node can contain multiple keys. It maintains balance by ensuring that:
1. Each node has at most **M - 1 keys**.
2. A non-leaf node with `k` keys has exactly `k + 1` children.
3. The tree grows upwards, meaning the root node may split when full, increasing the tree height.

## Code Structure
```
├── .gitignore (To ignore the binary)
├── btree.c  (Main implementation file)
└── README.md (This file)
```

## Functions Explained
### 1. `createNode(bool is_leaf)`
Allocates memory for a new B-tree node and initializes it as a **leaf or non-leaf**.

### 2. `splitChild(struct BTreeNode *parent, int index)`
Splits a full child node into two halves and pushes the middle key up to the parent.

### 3. `insertNonFull(struct BTreeNode *node, int key)`
Handles insertion into a node that is **not full**, placing the key in the correct position.

### 4. `insert(struct BTreeNode **root, int key)`
Manages insertion at the root level. If the root is full, it creates a new root and splits the existing one.

### 5. `traverse(struct BTreeNode *root)`
Performs an **in-order traversal** to print the B-tree in sorted order.

## Compilation and Execution
### **Compile the Code**
Use the following command:
```sh
gcc btree.c -o btree
```
### **Run the Program**
```sh
./btree
```

## Example Usage
```c
struct BTreeNode *root = NULL;
insert(&root, 1);
insert(&root, 2);
insert(&root, 3);
insert(&root, 4);
insert(&root, 5);
insert(&root, 6);
traverse(root);  // Output: 1 2 3 4 5 6
```

## Potential Issues
- **Segmentation Fault:** If `node->children[i]` is NULL, ensure all child nodes are initialized properly.
- **Memory Allocation Failure:** Always check if `malloc()` returns NULL.

## References
- [B-Trees on GeeksforGeeks](https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/)
- [Wikipedia: B-Trees](https://en.wikipedia.org/wiki/B-tree)


