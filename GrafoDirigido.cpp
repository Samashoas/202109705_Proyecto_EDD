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

GrafoDirigido::NodoGrafo* GrafoDirigido::encontrarNodo(const std::string& origen)const {
    for (size_t i = 0; i < nodos.size(); ++i) {
        if (nodos[i].origen == origen) {
            return const_cast<NodoGrafo*>(&nodos[i]);
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

void GrafoDirigido::FindShortcut(const std::string& origen, const std::string& destino) const {
    // Inicialización
    std::vector<std::string> vertices;
    std::vector<int> distancias;
    std::vector<std::string> anteriores;
    std::vector<bool> visitados;

    for (const auto& nodo : nodos) {
        vertices.push_back(nodo.origen);
        distancias.push_back(std::numeric_limits<int>::max());
        anteriores.push_back("");
        visitados.push_back(false);
    }

    int idxOrigen = -1;
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == origen) {
            idxOrigen = i;
            break;
        }
    }

    if (idxOrigen == -1) {
        std::cerr << "La ciudad origen no se encuentra en el grafo." << std::endl;
        return;
    }

    distancias[idxOrigen] = 0;

    while (true) {
        // Encuentra el vértice no visitado con la menor distancia
        int minDistancia = std::numeric_limits<int>::max();
        int u = -1;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!visitados[i] && distancias[i] < minDistancia) {
                minDistancia = distancias[i];
                u = i;
            }
        }

        if (u == -1 || vertices[u] == destino) break;

        visitados[u] = true;

        // Actualiza las distancias de los vértices adyacentes
        NodoGrafo* nodo = encontrarNodo(vertices[u]);
        if (nodo) {
            for (const auto& arista : nodo->adyacencias) {
                int v = -1;
                for (size_t i = 0; i < vertices.size(); ++i) {
                    if (vertices[i] == arista.destino) {
                        v = i;
                        break;
                    }
                }

                if (v != -1 && !visitados[v] && distancias[u] + arista.distancia < distancias[v]) {
                    distancias[v] = distancias[u] + arista.distancia;
                    anteriores[v] = vertices[u];
                }
            }
        }
    }

    // Mostrar la ruta más corta
    int idxDestino = -1;
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == destino) {
            idxDestino = i;
            break;
        }
    }

    if (idxDestino == -1) {
        std::cerr << "La ciudad destino no se encuentra en el grafo." << std::endl;
        return;
    }

    if (distancias[idxDestino] == std::numeric_limits<int>::max()) {
        std::cout << "No hay ruta disponible desde " << origen << " hasta " << destino << "." << std::endl;
        return;
    }

    std::vector<std::string> ruta;
    for (std::string v = destino; !v.empty(); ) {
        ruta.push_back(v);
        int idx = -1;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == v) {
                idx = i;
                break;
            }
        }
        v = anteriores[idx];
    }

    for (int i = 0; i < ruta.size() / 2; ++i) {
        std::swap(ruta[i], ruta[ruta.size() - 1 - i]);
    }

    std::cout << "La ruta más corta desde " << origen << " hasta " << destino << " es:" << std::endl;
    for (const auto& ciudad : ruta) {
        std::cout << ciudad << " ";
    }
    std::cout << "\nDistancia total: " << distancias[idxDestino] << std::endl;
}