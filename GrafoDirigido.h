//
// Created by jpsam on 30/06/2024.
//

#ifndef GRAFODIRIGIDO_H
#define GRAFODIRIGIDO_H
#include <vector>
#include <string>
#include <iostream>
#include <limits>


class GrafoDirigido {
private:
    struct Arista {
        std::string destino;
        int distancia;

        Arista(const std::string& dest, int dist) : destino(dest), distancia(dist) {}
    };

    struct NodoGrafo {
        std::string origen;
        std::vector<Arista> adyacencias;

        NodoGrafo(const std::string& orig) : origen(orig) {}
    };

    std::vector<NodoGrafo> nodos;

    NodoGrafo* encontrarNodo(const std::string& origen) const;

public:
    GrafoDirigido();
    ~GrafoDirigido();

    void agregarArista(const std::string& origen, const std::string& destino, int distancia);
    void mostrarGrafo() const;
    void generarArchivoDOT(const std::string& nombreDOT = "grafo.dot") const;
    void FindShortcut(const std::string& origen, const std::string& destino) const;
};



#endif //GRAFODIRIGIDO_H
