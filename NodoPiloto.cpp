//
// Created by jpsam on 01/07/2024.
//
#include "NodoPiloto.h"

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

void NodoPilotos::setPiloto(const Piloto& piloto) {
    this->pilot = piloto;
}