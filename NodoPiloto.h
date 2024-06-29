//
// Created by jpsam on 28/06/2024.
//

#ifndef NODOPILOTO_H
#define NODOPILOTO_H
#include <iostream>
#include <fstream>
using namespace std;
#include "CargaPilotos.h"


class NodoPilotos {
private:
    Piloto pilot;
    NodoPilotos* siguiente;
    NodoPilotos* anterior;

public:
    NodoPilotos(Piloto piloto);
    NodoPilotos* getSiguiente();
    NodoPilotos* getAnterior();
    void setSiguiente(NodoPilotos* siguiente);
    void setAnterior(NodoPilotos* anterior);
    Piloto getPiloto();
};

NodoPilotos::NodoPilotos(Piloto pilot) : pilot(pilot), siguiente(nullptr), anterior(nullptr) {}

NodoPilotos* NodoPilotos::getSiguiente() {
    return siguiente;
}

NodoPilotos* NodoPilotos::getAnterior() {
    return anterior;
}

void NodoPilotos::setSiguiente(NodoPilotos* siguiente) {
    this->siguiente = siguiente;
}

void NodoPilotos::setAnterior(NodoPilotos* anterior) {
    this->anterior = anterior;
}

Piloto NodoPilotos::getPiloto() {
    return pilot;
}

#endif //NODOPILOTO_H
