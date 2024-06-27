//
// Created by jpsam on 27/06/2024.
//

#ifndef BTREE_H
#define BTREE_H
#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
#include "CargaAviones.h"

class BTreeNode {
public:
    std::vector<Avion> keys;    // Vector de claves
    std::vector<BTreeNode*> children; // Vector de punteros a hijos
    bool isLeaf;                // Indicador de si es una hoja

    BTreeNode(bool leaf);

    void insertNonFull(const Avion& avion, int t);
    void splitChild(int i, BTreeNode* y, int t);
    void traverse();

    BTreeNode* search(const std::string& vuelo);

    friend class BTree;
};

// Definición del árbol B
class BTree {
public:
    BTreeNode* root; // Puntero a la raíz
    int t;           // Grado mínimo

    BTree(int t);

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode* search(const std::string& vuelo) {
        return (root == nullptr) ? nullptr : root->search(vuelo);
    }

    void insert(const Avion& avion);
};

BTreeNode::BTreeNode(bool leaf) {
    isLeaf = leaf;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        std::cout << " " << keys[i].numero_de_registro;
    }

    if (!isLeaf) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(const std::string& vuelo) {
    int i = 0;
    while (i < keys.size() && vuelo > keys[i].vuelo) {
        i++;
    }

    if (i < keys.size() && keys[i].vuelo == vuelo) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return children[i]->search(vuelo);
}

BTree::BTree(int t) {
    this->t = t;
    root = nullptr;
}

void BTree::insert(const Avion& avion) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(avion);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children.push_back(root);
            s->splitChild(0, root, t);
            int i = 0;
            if (s->keys[0].vuelo < avion.vuelo) {
                i++;
            }
            s->children[i]->insertNonFull(avion, t);
            root = s;
        } else {
            root->insertNonFull(avion, t);
        }
    }
}

void BTreeNode::insertNonFull(const Avion& avion, int t) {
    int i = keys.size() - 1;
    if (isLeaf) {
        keys.resize(keys.size() + 1);
        while (i >= 0 && keys[i].vuelo > avion.vuelo) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = avion;
    } else {
        while (i >= 0 && keys[i].vuelo > avion.vuelo) {
            i--;
        }
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1], t);
            if (keys[i + 1].vuelo < avion.vuelo) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(avion, t);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y, int t) {
    BTreeNode* z = new BTreeNode(y->isLeaf);
    z->keys.resize(t - 1);

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->isLeaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }

    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);

    y->keys.resize(t - 1);
}


#endif //BTREE_H
