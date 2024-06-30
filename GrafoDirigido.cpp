//
// Created by jpsam on 30/06/2024.
//

#include "GrafoDirigido.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

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

void GrafoDirigido::generarArchivoDOT(const std::string& nombreDOT) const {
    std::ofstream archivo(nombreDOT);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreDOT << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "    rankdir=TB;\n"; // Direccion de izquierda a derecha
    archivo << "    splines=false;\n"; // Permitir splines
    archivo << "    overlap=false;\n"; // Evitar sobreposición

    for (const auto& nodo : nodos) {
        for (const auto& arista : nodo.adyacencias) {
            archivo << "    \"" << nodo.origen << "\" -> \"" << arista.destino << "\" [label=\"" << arista.distancia << "\"];\n";
        }
    }
    archivo << "}\n";

    archivo.close();

    // Llamar a Graphviz para generar la imagen
    std::string comando = "dot -Tpng " + nombreDOT + " -o grafo.png";
    system(comando.c_str());

    system("grafo.png");

    std::cout << "Imagen del grafo generada como grafo.png" << std::endl;
}