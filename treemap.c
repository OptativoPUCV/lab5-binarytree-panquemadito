#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *newMap  = (TreeMap *)malloc(sizeof(TreeMap)) ;
    if (newMap == NULL) {
        return NULL;
    }
    newMap->root = NULL;
    newMap->current = NULL;
    newMap->lower_than = lower_than;

    return newMap;

}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode *parent = NULL;
    TreeNode *current = tree->root;

    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            return;
        }
    }
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode)) ;
    if (newNode == NULL) return;

    newNode->pair = (Pair*) malloc(sizeof(Pair)) ;
    if (newNode->pair == NULL) {
        free(newNode) ;
        return;
    }
    newNode->pair->key = key;
    newNode->pair->value = value;

    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    
    if (parent == NULL) {
        tree->root = newNode;
    } else if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    tree->current = newNode;

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode *node = tree->root;

    while (node != NULL)  {
        if (tree->lower_than(key, node->pair->key)) {
            node = node->left;
        } else if (tree->lower_than(node->pair->key, key)) {
            node = node->right;
        } else {
            tree->current = node;
            return node->pair;
        }
    }
    tree->current = NULL;
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
