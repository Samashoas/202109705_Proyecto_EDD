//
// Created by jpsam on 29/06/2024.
//

#ifndef THASH_H
#define THASH_H
#include "CargaPilotos.h"

class NodoHash {
public:
    Piloto piloto;
    NodoHash* siguiente;

    NodoHash(Piloto p) : piloto(p), siguiente(nullptr) {}
};

class TablaHash {
private:
    int M;  // tamaño de la tabla
    NodoHash** tabla;  // array de punteros a nodos

public:
    TablaHash(int tam) : M(tam) {
        tabla = new NodoHash*[M];
        for (int i = 0; i < M; i++) {
            tabla[i] = nullptr;
        }
    }

    ~TablaHash() {
        for (int i = 0; i < M; i++) {
            NodoHash* actual = tabla[i];
            while (actual) {
                NodoHash* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] tabla;
    }

    int funcionHash(std::string llave) {
        int suma = 0;
        for (char c : llave) {
            suma += c;
        }
        return suma % M;
    }

    void insertar(Piloto p) {
        int indice = funcionHash(p.numero_de_id);
        NodoHash* nuevo = new NodoHash(p);
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;
    }

    Piloto buscar(std::string llave) {
        int indice = funcionHash(llave);
        NodoHash* actual = tabla[indice];
        while (actual) {
            if (actual->piloto.numero_de_id == llave) {
                return actual->piloto;
            }
            actual = actual->siguiente;
        }
        throw std::runtime_error("Piloto no encontrado");
    }

    void eliminar(std::string llave) {
        int indice = funcionHash(llave);
        NodoHash* actual = tabla[indice];
        NodoHash* previo = nullptr;
        while (actual) {
            if (actual->piloto.numero_de_id == llave) {
                if (previo) {
                    previo->siguiente = actual->siguiente;
                } else {
                    tabla[indice] = actual->siguiente;
                }
                delete actual;
                return;
            }
            previo = actual;
            actual = actual->siguiente;
        }
        throw std::runtime_error("Piloto no encontrado");
    }

    void imprimir() {
        for (int i = 0; i < M; i++) {
            NodoHash* actual = tabla[i];
            while (actual) {
                std::cout << "Indice: " << i << std::endl;
                std::cout << "Numero de ID: " << actual->piloto.numero_de_id << std::endl;
                std::cout << "------------------------" << std::endl;
                actual = actual->siguiente;
            }
        }
    }

    void generarReporte() {
        std::ofstream archivo("hash_reporte.dot");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo");
        }

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";  // Cambia la dirección del grafo de izquierda a derecha
        archivo << "node [shape=record];\n";

        // Crear los nodos para los índices de la tabla
        for (int i = 0; i < M; i++) {
            archivo << "index" << i << " [label=\"" << i << "\", shape=box, style=filled, fillcolor=orange];\n";
        }

        // Crear los nodos para los pilotos y las conexiones
        for (int i = 0; i < M; i++) {
            NodoHash* actual = tabla[i];
            if (actual) {
                int nodo_id = 0;
                std::string prev_node = "index" + std::to_string(i);
                while (actual) {
                    std::string current_node = "nodo" + std::to_string(i) + "_" + std::to_string(nodo_id);
                    archivo << current_node << " [label=\"{" << actual->piloto.numero_de_id << "}\", shape=record, style=filled, fillcolor=lightblue];\n";
                    archivo << prev_node << " -> " << current_node << ";\n";
                    prev_node = current_node;
                    actual = actual->siguiente;
                    nodo_id++;
                }
            }
        }

        archivo << "}\n";
        archivo.close();
        system("dot -Tpng hash_reporte.dot -o hash_reporte.png");
        system("start hash_reporte.png");
    }
};

#endif //THASH_H
