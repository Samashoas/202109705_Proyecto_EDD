#ifndef GRAFODIRIGIDO_H
#define GRAFODIRIGIDO_H

#include <string>
#include <iostream>
#include <limits>
#include "ListaAdyacencia.h"
#include <vector>  // Necesario para el algoritmo de Dijkstra
#include <fstream>

class GrafoDirigido {
private:
    NodoGrafo* nodos;

    NodoGrafo* encontrarNodo(const std::string& origen) const;
    NodoGrafo* encontrarNodoOCrear(const std::string& origen);

public:
    GrafoDirigido();
    ~GrafoDirigido();

    void agregarArista(const std::string& origen, const std::string& destino, int distancia);
    void mostrarGrafo() const;
    void generarArchivoDOT(const std::string& nombreDOT = "grafo.dot") const;
    void FindShortcut(const std::string& origen, const std::string& destino) const;
    void eliminarNodosYAdyacencias(NodoGrafo* nodo);
};

#endif // GRAFODIRIGIDO_H
