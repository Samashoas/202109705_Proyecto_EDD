//
// Created by jpsam on 29/06/2024.
//

#ifndef THASH_H
#define THASH_H
#include "ListaSimple.h"

class TablaHash {
private:
    int M;  // tamaño de la tabla
    ListaSimple* tabla;  // array de listas simples

public:
    TablaHash(int tam) : M(tam) {
        tabla = new ListaSimple[M];
    }

    ~TablaHash() {
        delete[] tabla;
    }

    int funcionHash(std::string llave) {
        int suma = static_cast<int>(llave[0]);
        for (size_t i = 1; i < llave.length(); ++i) {
            suma += (llave[i] - '0');
        }
        return suma % M;
    }

    void insertar(Piloto p) {
        int indice = funcionHash(p.numero_de_id);
        tabla[indice].insertar(p);
    }

    Piloto buscar(std::string llave) {
        int indice = funcionHash(llave);
        return tabla[indice].buscar(llave);
    }

    void eliminar(std::string llave) {
        int indice = funcionHash(llave);
        tabla[indice].eliminar(llave);
    }

    void imprimir() {
        for (int i = 0; i < M; i++) {
            tabla[i].imprimir(i);
        }
    }

    void generarReporte() {
        std::ofstream archivo("hash_reporte.dot");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo");
        }

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";  // Cambia la dirección del grafo de izquierda a derecha
        archivo << "labelloc=\"t\";\n"; // Posiciona la etiqueta en la parte superior
        archivo << "label=\"Tabla Hash Pilotos\";\n"; // Define la etiqueta (título)
        archivo << "node [shape=record];\n";

        // Crear los nodos para los índices de la tabla
        for (int i = 0; i < M; i++) {
            archivo << "index" << i << " [label=\"" << i << "\", shape=box, style=filled];\n"; // Se eliminó fillcolor=orange
        }

        // Crear los nodos para los pilotos y las conexiones
        for (int i = 0; i < M; i++) {
            tabla[i].generarReporte(archivo, i);
        }

        archivo << "}\n";
        archivo.close();
        system("dot -Tpng hash_reporte.dot -o hash_reporte.png");
        system("start hash_reporte.png");
    }
};

#endif //THASH_H
