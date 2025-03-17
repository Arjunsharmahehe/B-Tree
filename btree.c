#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 4 // Define the order of the tree

struct BTreeNode{
    int num_keys;                      // Number of keys in the node
    int keys[M - 1];                   // Array of keys
    struct BTreeNode *children[M];     // Array of children node pointers
    bool is_leaf;                      // True if node is a leaf node
};

struct BTreeNode *createNode(bool is_leaf){
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;

    // Setting all the childrens to NULL as we don't want a garbage value their
    for(int i = 0; i < M; i++){
        newNode->children[i] = NULL;
    }

    return newNode;
}

void splitChild(struct BTreeNode *parent, int index){
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);

    newNode->num_keys = M/2 - 1;

    // Insert the right half keys into the new node
    for(int i = 0; i < M/2 - 1; i++)
        newNode->keys[i] = child->keys[i + M/2];

    // If not a leaf node, insert the right half children nodes as well
    if (!child->is_leaf)
        for(int i = 0; i < M/2; i++)
            newNode->children[i] = child->children[i + M/2];

    child->num_keys = M/2 - 1;

    // Shift parents children to make room for the new node
    for (int i = parent->num_keys; i > index; i--)
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = newNode;

    // Shift parents keys to make room for the new node
    for (int i = parent->num_keys - 1; i >= index; i--)
        parent->keys[i + 1] = parent->keys[i];

    // Adding the middle key to the parent
    parent->keys[index] = child->keys[M/2 - 1];
    parent->num_keys++;
}

void insertNonFull(struct BTreeNode *node, int key){
    int i = node->num_keys - 1;

    if (node->is_leaf){
        // Insert the node into sorted position if it's a leaf node
        while (i >= 0 && node->keys[i] > key){
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Find the child to insert the key into
        while (i >= 0 && node->keys[i] > key) 
            i--;
        i++;

        // Split child if it's full
        if (node->children[i]->num_keys == M - 1) {
            splitChild(node, i);
            
            // Determine which of the two children is the new one
            if (node->keys[i] < key) {
                i++;
            }
        }
        // Insert the node in the new node
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key
void insert(struct BTreeNode **root, int key){
    struct BTreeNode *node = *root;

    if (node == NULL){
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if (node->num_keys == M - 1){
            // Split the node
            struct BTreeNode *newRoot = createNode(false);
            newRoot->children[0] = node;
            splitChild(newRoot, 0);
            *root = newRoot;
        }
        insertNonFull(*root, key);
    }
}

// Function to traverse and print the B-tree in-order
void traverse(struct BTreeNode *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->children[i]);
    }
}

// Main function to test B-tree implementation
int main() {
    struct BTreeNode *root = NULL;

    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 6);

    printf("In-order traversal of the B-tree: ");
    traverse(root);
    printf("\n");

    return 0;
}