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

// Ejercicio 1 LAB 5
// Esta función crea un nuevo mapa ordenado (TreeMap) e inicializa sus variables, incluida la función de comparación de claves.

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    //new->lower_than = lower_than;

    TreeMap * mapa= (TreeMap*)malloc(sizeof(TreeMap));
    if(mapa == NULL){

        return NULL;
    }

    mapa->root = NULL;
    mapa->current = NULL;
    mapa->lower_than = lower_than;
    
    return mapa;
}


// Ejercicio 3
// La función insertTreeMap inserta un nuevo dato (clave-valor) en el árbol TreeMap.



void insertTreeMap(TreeMap* tree, void* key, void* value) {
    Pair* newPair = (Pair*)malloc(sizeof(Pair));
    if (newPair == NULL) {
        exit(EXIT_FAILURE);
    }
    newPair->key = key;
    newPair->value = value;

    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->pair = newPair;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
    } else {
        TreeNode* current = tree->root;
        TreeNode* parent;
        while (current != NULL) {
            parent = current;
            if (tree->lower_than(key, current->pair->key)) {
                current = current->left;
            } else if (tree->lower_than(current->pair->key, key)) {
                current = current->right;
            } else {
                current->pair->value = value;
                free(newPair); 
                free(newNode); 
                tree->current = current; 
                return;
            }
        }
        newNode->parent = parent;
        if (tree->lower_than(key, parent->pair->key)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        tree->current = newNode; 
    }
}

//Ejercicio 4
// La función minimum que busca el nodo con la clave mínima en el subárbol con raíz en un nodo dado x.

TreeNode * minimum(TreeNode * x){
    if (x == NULL){
        return NULL;
    }
    while (x->left != NULL){
        x = x->left;
    }
    return x;
}

//Ejercicio 5
// Elimina el nodo de un arbol considerando 3 casos

void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL){
        return;
    }

    if (node->left == NULL && node->right == NULL){
        if (node->parent == NULL){

            tree->root = NULL;
            
        } else {

            if (node->parent->left == node){
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }

        free(node->pair);
        free(node);
    }

    else if (node->left == NULL || node->right == NULL){
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        if (node->parent == NULL){

            tree->root = child;
        } else {
            if (node->parent->left == node){

                node->parent->left = child;
            }
            child->parent = node->parent;
        }

        free(node->pair);
        free(node);
        
    }

    else {
        TreeNode* minNode = minimum(node->right);
        node->pair = minNode->pair;
            eraseTreeMap(tree, minNode);
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


// Ejercicio 2:
// Esta función busca un nodo con una clave dada en el árbol y devuelve el par asociado a esa clave. Si no se encuentra la clave, devuelve NULL. La función también actualiza el puntero current del árbol al nodo encontrado o al nodo más cercano a la clave buscada.


Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    TreeNode * current = tree->root;
    while (current != NULL){
        if (is_equal(tree, current->pair->key, key)) {

            tree->current = current;
            return current->pair;
        }
        else if (tree->lower_than(key, current->pair->key)){


            current = current->left;
        }

        else {
            current = current->right;
        }

        
    }
    
    
    
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
