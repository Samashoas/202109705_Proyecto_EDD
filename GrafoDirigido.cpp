#include "GrafoDirigido.h"
#include <limits>

GrafoDirigido::GrafoDirigido() : nodos(nullptr) {}

GrafoDirigido::~GrafoDirigido() {
    NodoGrafo* actual = nodos;
    while (actual != nullptr) {
        NodoGrafo* siguienteNodo = actual->siguiente;
        eliminarNodosYAdyacencias(actual);
        actual = siguienteNodo;
    }
}

void GrafoDirigido::eliminarNodosYAdyacencias(NodoGrafo* nodo) {
    NodoAdyacencia* actualAdyacencia = nodo->adyacencias;
    while (actualAdyacencia != nullptr) {
        NodoAdyacencia* siguienteAdyacencia = actualAdyacencia->siguiente;
        delete actualAdyacencia;
        actualAdyacencia = siguienteAdyacencia;
    }
    delete nodo;
}

NodoGrafo* GrafoDirigido::encontrarNodo(const std::string& origen) const {
    NodoGrafo* actual = nodos;
    while (actual != nullptr) {
        if (actual->origen == origen) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void GrafoDirigido::agregarArista(const std::string& origen, const std::string& destino, int distancia) {
    NodoGrafo* nodoOrigen = encontrarNodo(origen);
    if (nodoOrigen == nullptr) {
        nodoOrigen = new NodoGrafo(origen);
        nodoOrigen->siguiente = nodos;
        nodos = nodoOrigen;
    }

    NodoAdyacencia* nuevaAdyacencia = new NodoAdyacencia(destino, distancia);
    nuevaAdyacencia->siguiente = nodoOrigen->adyacencias;
    nodoOrigen->adyacencias = nuevaAdyacencia;
}

void GrafoDirigido::mostrarGrafo() const {
    NodoGrafo* actual = nodos;
    while (actual != nullptr) {
        std::cout << "Origen: " << actual->origen << std::endl;
        NodoAdyacencia* actualAdyacencia = actual->adyacencias;
        while (actualAdyacencia != nullptr) {
            std::cout << "  -> " << actualAdyacencia->destino << " (Distancia: " << actualAdyacencia->distancia << ")" << std::endl;
            actualAdyacencia = actualAdyacencia->siguiente;
        }
        actual = actual->siguiente;
    }
}

void GrafoDirigido::generarArchivoDOT(const std::string& nombreDOT) const {
    std::ofstream archivo(nombreDOT);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreDOT << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    NodoGrafo* actual = nodos;
    while (actual != nullptr) {
        NodoAdyacencia* actualAdyacencia = actual->adyacencias;
        while (actualAdyacencia != nullptr) {
            archivo << "    \"" << actual->origen << "\" -> \"" << actualAdyacencia->destino << "\" [label=\"" << actualAdyacencia->distancia << "\"];\n";
            actualAdyacencia = actualAdyacencia->siguiente;
        }
        actual = actual->siguiente;
    }
    archivo << "}\n";
    archivo.close();

    // Llamar a Graphviz para generar la imagen
    std::string comando = "dot -Tpng " + nombreDOT + " -o grafo.png";
    system(comando.c_str());
    system("start grafo.png");
}

void GrafoDirigido::FindShortcut(const std::string& origen, const std::string& destino) const {
    // Inicialización
    std::vector<std::string> vertices;
    std::vector<int> distancias;
    std::vector<std::string> anteriores;
    std::vector<bool> visitados;

    NodoGrafo* actual = nodos;
    while (actual != nullptr) {
        vertices.push_back(actual->origen);
        distancias.push_back(std::numeric_limits<int>::max());
        anteriores.push_back("");
        visitados.push_back(false);
        actual = actual->siguiente;
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
            NodoAdyacencia* adyacente = nodo->adyacencias;
            while (adyacente != nullptr) {
                int v = -1;
                for (size_t i = 0; i < vertices.size(); ++i) {
                    if (vertices[i] == adyacente->destino) {
                        v = i;
                        break;
                    }
                }

                if (v != -1 && !visitados[v] && distancias[u] + adyacente->distancia < distancias[v]) {
                    distancias[v] = distancias[u] + adyacente->distancia;
                    anteriores[v] = vertices[u];
                }
                adyacente = adyacente->siguiente;
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
