//
// Created by jpsam on 02/07/2024.
//

#ifndef LISTAADYACENCIA_H
#define LISTAADYACENCIA_H
#include <string>

struct NodoAdyacencia {
    std::string destino;
    int distancia;
    NodoAdyacencia* siguiente;

    NodoAdyacencia(const std::string& dest, int dist)
        : destino(dest), distancia(dist), siguiente(nullptr) {}
};

struct NodoGrafo {
    std::string origen;
    NodoAdyacencia* adyacencias;
    NodoGrafo* siguiente;

    NodoGrafo(const std::string& orig)
        : origen(orig), adyacencias(nullptr), siguiente(nullptr) {}
};
#endif //LISTAADYACENCIA_H
