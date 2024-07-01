//
// Created by jpsam on 30/06/2024.
//

#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
#include "NodoListaSimple.h"

class ListaSimple {
private:
    NodoLista* cabeza;

public:
    ListaSimple() : cabeza(nullptr) {}

    ~ListaSimple() {
        NodoLista* actual = cabeza;
        while (actual) {
            NodoLista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertar(Piloto p) {
        NodoLista* nuevo = new NodoLista(p);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    Piloto buscar(std::string llave) {
        NodoLista* actual = cabeza;
        while (actual) {
            if (actual->piloto.numero_de_id == llave) {
                return actual->piloto;
            }
            actual = actual->siguiente;
        }
        throw std::runtime_error("Piloto no encontrado");
    }

    void eliminar(std::string llave) {
        NodoLista* actual = cabeza;
        NodoLista* previo = nullptr;
        while (actual) {
            if (actual->piloto.numero_de_id == llave) {
                if (previo) {
                    previo->siguiente = actual->siguiente;
                } else {
                    cabeza = actual->siguiente;
                }
                delete actual;
                return;
            }
            previo = actual;
            actual = actual->siguiente;
        }
        throw std::runtime_error("Piloto no encontrado");
    }

    void imprimir(int indice) {
        NodoLista* actual = cabeza;
        while (actual) {
            std::cout << "Indice: " << indice << std::endl;
            std::cout << "Numero de ID: " << actual->piloto.numero_de_id << std::endl;
            std::cout << "------------------------" << std::endl;
            actual = actual->siguiente;
        }
    }

    void generarReporte(std::ofstream& archivo, int indice) {
        NodoLista* actual = cabeza;
        int nodo_id = 0;
        std::string prev_node = "index" + std::to_string(indice);
        while (actual) {
            std::string current_node = "nodo" + std::to_string(indice) + "_" + std::to_string(nodo_id);
            archivo << current_node << " [label=\"{" << actual->piloto.numero_de_id << "}\", shape=record, style=filled, fillcolor=lightblue];\n";
            archivo << prev_node << " -> " << current_node << ";\n";
            prev_node = current_node;
            actual = actual->siguiente;
            nodo_id++;
        }
    }
};
#endif //LISTASIMPLE_H
