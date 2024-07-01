//
// Created by jpsam on 13/06/2024.
//

#ifndef CIRCULARDOBLEMAN_H
#define CIRCULARDOBLEMAN_H
#include "nodoAv.h"

class ListaCircularMan
{
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaCircularMan();
    bool estaVacia();
    void insertarInicio(Avion dato);
    void insertarFinal(Avion dato);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void generarReporte();
    ~ListaCircularMan();
};

ListaCircularMan::ListaCircularMan()
{
    primero = nullptr;
    ultimo = nullptr;
}

bool ListaCircularMan::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

void ListaCircularMan::insertarInicio(Avion dato)
{
    Nodo *nuevo = new Nodo(dato);
    if (estaVacia())
    {
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        primero->setAnterior(nuevo);
        ultimo->setSiguiente(nuevo);
        primero = nuevo;
    }
}

void ListaCircularMan::insertarFinal(Avion dato)
{
    Nodo *nuevo = new Nodo(dato);
    if (estaVacia())
    {
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        primero->setAnterior(nuevo);
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;
    }
}

void ListaCircularMan::eliminarInicio()
{
    if (estaVacia())
    {
        std::cout << "La lista está vacía" << std::endl;
    }
    else
    {
        if (primero == ultimo)
        {
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            Nodo *segundo = primero->getSiguiente();
            segundo->setAnterior(ultimo);
            ultimo->setSiguiente(segundo);
            delete primero;
            primero = segundo;
        }
    }
}

void ListaCircularMan::eliminarFinal()
{
    if (estaVacia())
    {
        std::cout << "La lista está vacía" << std::endl;
    }
    else
    {
        if (primero == ultimo)
        {
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            Nodo *temporal = primero;
            while (temporal->getSiguiente() != ultimo)
            {
                temporal = temporal->getSiguiente();
            }
            temporal->setSiguiente(primero);
            primero->setAnterior(temporal);
            delete ultimo;
            ultimo = temporal;
        }
    }
}

void ListaCircularMan::visualizarLista()
{
    if (estaVacia())
    {
        std::cout << "La lista está vacía" << std::endl;
    }
    else
    {
        Avion nodoDato;
        Nodo *actual = primero;
        do
        {
            nodoDato = actual->getDato();
            std::cout << nodoDato.numero_de_registro << std::endl; // Imprime el número de vuelo
            actual = actual->getSiguiente();
        } while (actual != primero);
    }
}

void ListaCircularMan::generarReporte(){
    if (estaVacia()){
        std::cout << "La lista está vacía\n" << std::endl;
    }
    else
    {
        std::ofstream archivo;
        archivo.open("grafica_LC_Mantenimiento.dot", std::ios::out);
        archivo << "digraph G { rankdir=LR; node [shape=oval];" << std::endl;

        Avion nodoDato;
        Nodo *actual = primero;
        int nodeCount = 0;
        do
        {
            nodoDato = actual->getDato();
            archivo << "node" << nodeCount << " [label=\"" << nodoDato.numero_de_registro << "\"];" << std::endl; // Escribe el número de vuelo
            actual = actual->getSiguiente();
            nodeCount++;
        } while (actual != primero);

        actual = primero;
        int currentNode = 0;
        do
        {
            int nextNode = (currentNode + 1) % nodeCount;
            archivo << "node" << currentNode << " -> node" << nextNode << ";" << std::endl;
            archivo << "node" << nextNode << " -> node" << currentNode << ";" << std::endl;
            actual = actual->getSiguiente();
            currentNode++;
        } while (actual != primero);

        archivo << " }";
        archivo.close();
        system("dot -Tpng grafica_LC_Mantenimiento.dot -o grafica_LC_Mantenimiento.png");
        system("start grafica_LC_Mantenimiento.png");
    }
}

ListaCircularMan::~ListaCircularMan()
{
    while (!estaVacia()) {
        eliminarInicio();
    }
}

#endif //CIRCULARDOBLEMAN_H
