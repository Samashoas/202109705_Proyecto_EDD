#ifndef NODOAV_H
#define NODOAV_H
#include "CargaAviones.h"

class Nodo
{
private:
    Avion dato;
    Nodo *anterior;
    Nodo *siguiente;
public:
    Nodo(Avion dato);
    Nodo *getSiguiente();
    Nodo *getAnterior();
    void setSiguiente(Nodo *siguiente);
    void setAnterior(Nodo *anterior);
    Avion getDato();
    void setDato(Avion dato);
    ~Nodo();
};

Nodo::Nodo(Avion dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

Nodo* Nodo::getSiguiente(){
    return this->siguiente;
}

Nodo* Nodo::getAnterior(){
    return this->anterior;
}

void Nodo::setSiguiente(Nodo *siguiente){
    this->siguiente = siguiente;
}

void Nodo::setAnterior(Nodo *anterior){
    this->anterior = anterior;
}

Avion Nodo::getDato(){
    return this->dato;
}

Nodo::~Nodo()
{
}

#endif //NODOAV_H