#ifndef ARBOLBB_H
#define ARBOLBB_H

#include "NodoPiloto.h"
#include <fstream>
#include <iostream>

#include "NodoPiloto.h"
#include <fstream>
#include <iostream>

class ArbolBB {
private:
    NodoPilotos* raiz;
    std::ofstream archivo;
    Piloto nodoDato;

    NodoPilotos* eliminarNodo(NodoPilotos* nodoPtr, int horas_de_vuelo);
    NodoPilotos* encontrarMinimo(NodoPilotos* nodoPtr);
    NodoPilotos* encontrarMaximo(NodoPilotos* nodoPtr);
    NodoPilotos* buscarNodoPorId(NodoPilotos* nodoPtr, const std::string& numero_de_id);

public:
    int recorrido = 0;
    ArbolBB();
    bool estaVacio();
    void insertar(Piloto dato);
    NodoPilotos* insertarNodo(Piloto dato, NodoPilotos* nodoPtr);
    void buscar(Piloto dato);
    Piloto buscarNodo(Piloto dato, NodoPilotos* nodoPtr);
    void eliminarPorId(const std::string& numero_de_id);

    // Recorridos
    void RecorridoPreorden(NodoPilotos* nodoPtr);
    void RecorridoInorden(NodoPilotos* nodoPtr);
    void RecorridoPostorden(NodoPilotos* nodoPtr);
    void imprimirPreorden();
    void imprimirInorden();
    void imprimirPostorden();

    void generarReporte();
    void imprimirNodo(NodoPilotos* nodoPtr);
    ~ArbolBB();
};

#endif // ARBOLBB_H