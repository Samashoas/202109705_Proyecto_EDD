//
// Created by jpsam on 30/06/2024.
//

#ifndef NODOLISTASIMPLE_H
#define NODOLISTASIMPLE_H
#include "CargaPilotos.h"

class NodoLista {
public:
    Piloto piloto;
    NodoLista* siguiente;

    NodoLista(Piloto p) : piloto(p), siguiente(nullptr) {}
};

#endif //NODOLISTASIMPLE_H
