#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
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
    void generateGraphviz(std::ostream& out, int& index) const;

    BTreeNode* search(const std::string& NV);

    friend class BTree;
};

class BTree {
public:
    BTreeNode* root; // Puntero a la raíz
    int t;           // Grado mínimo

    BTree(int t);

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode* search(const std::string& NV) {
        return (root == nullptr) ? nullptr : root->search(NV);
    }

    void insert(const Avion& avion);

    void generateGraphviz(std::ostream& out) const {
        out << "digraph G {\n";
        out << "node [shape=record];\n";
        out << "rank=same;\n";
        int index = 0;
        if (root != nullptr) root->generateGraphviz(out, index);
        out << "}\n";
    }

    void visualizar() const {
        std::ofstream outFile("btree.dot");
        if (outFile.is_open()) {
            generateGraphviz(outFile);
            outFile.close();
            std::system("dot -Tpng btree.dot -o btree.png");
            std::system("btree.png");
        } else {
            std::cerr << "No se pudo abrir el archivo para escribir\n";
        }
    }
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

BTreeNode* BTreeNode::search(const std::string& NV) {
    int i = 0;
    while (i < keys.size() && NV > keys[i].numero_de_registro) {
        i++;
    }

    if (i < keys.size() && keys[i].numero_de_registro == NV) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return children[i]->search(NV);
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
            if (s->keys[0].numero_de_registro < avion.numero_de_registro) {
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
        while (i >= 0 && keys[i].numero_de_registro > avion.numero_de_registro) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = avion;
    } else {
        while (i >= 0 && keys[i].numero_de_registro > avion.numero_de_registro) {
            i--;
        }
        i++;
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i], t);
            if (keys[i].numero_de_registro < avion.numero_de_registro) {
                i++;
            }
        }
        children[i]->insertNonFull(avion, t);
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

    //y->keys.resize(t - 1);
}

void BTreeNode::generateGraphviz(std::ostream& out, int& index) const {
    int current_index = index++;
    out << "node" << current_index << " [label=\"";
    for (int i = 0; i < keys.size(); ++i) {
        if (i > 0) out << " | ";
        out << "<f" << i << "> " << keys[i].numero_de_registro;
    }
    out << "\"];\n";

    for (int i = 0; i < children.size(); ++i) {
        int child_index = index;
        if (!isLeaf) {
            children[i]->generateGraphviz(out, index);  // Mover la generación del hijo antes de la conexión
            //int key_index = i;
            //if( key_index < keys.size() ) {
               // out << "node" << current_index << ":f" << key_index << " -> node" << child_index << ";\n";
            //}else {
                //out << "node" << current_index << ":f" << (keys.size() - 1) << " -> node" << child_index << ";\n";
            //}
            out << "node" << current_index <<" -> node" << child_index << ";\n";
        }
    }
}

#endif // BTREE_H