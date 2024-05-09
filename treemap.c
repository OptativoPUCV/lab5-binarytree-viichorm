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



void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree->root == NULL){

        tree->root = (TreeNode*)malloc(sizeof(TreeNode));
        tree->root->pair = (Pair*)malloc(sizeof(Pair));
        tree->root->pair->key = key;
        tree->root->pair->value = value;
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->current = tree->root;
    } else {


        TreeNode * currentNode = tree->root;
        while (currentNode != NULL){

            int cmp = strcmp(key, currentNode->key){

                if (cmp < 0){

                    if (currentNode->left == NULL){

                    currentNode->left = (TreeNode*)malloc(sizeof(TreeNode))
                        currentNode->left->key = key;
                        currentNode->left->value = value;
                        currentNode->left->left = NULL;
                    currentNOde->left->right = NULL;
                    tree->current = currentNode->left;
                    return;
                    
                    }
                currentNOde= currentNode->left;
                }
            }
        }
    }

    

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
