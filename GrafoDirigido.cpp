//
// Created by jpsam on 30/06/2024.
//

#include "GrafoDirigido.h"

GrafoDirigido::GrafoDirigido() {
}

GrafoDirigido::~GrafoDirigido() {
}

GrafoDirigido::NodoGrafo* GrafoDirigido::encontrarNodo(const std::string& origen) {
    for (size_t i = 0; i < nodos.size(); ++i) {
        if (nodos[i].origen == origen) {
            return &nodos[i];
        }
    }
    return nullptr;
}

void GrafoDirigido::agregarArista(const std::string& origen, const std::string& destino, int distancia) {
    NodoGrafo* nodo = encontrarNodo(origen);
    if (!nodo) {
        nodos.emplace_back(origen);
        nodo = &nodos.back();
    }
    nodo->adyacencias.emplace_back(destino, distancia);
}

void GrafoDirigido::mostrarGrafo() const {
    for (const auto& nodo : nodos) {
        std::cout << nodo.origen << " -> ";
        for (const auto& arista : nodo.adyacencias) {
            std::cout << "(" << arista.destino << ", " << arista.distancia << ") ";
        }
        std::cout << std::endl;
    }
}