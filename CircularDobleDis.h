//
// Created by jpsam on 13/06/2024.
//

#ifndef CIRCULARDOBLEDIS_H
#define CIRCULARDOBLEDIS_H
#include "nodoAv.h"

class ListaCircularDis
{
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaCircularDis();
    bool estaVacia();
    void insertarInicio(Avion dato);
    void insertarFinal(Avion dato);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void generarReporte();
    ~ListaCircularDis();
};

ListaCircularDis::ListaCircularDis()
{
    primero = nullptr;
    ultimo = nullptr;
}

bool ListaCircularDis::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

void ListaCircularDis::insertarInicio(Avion dato)
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

void ListaCircularDis::insertarFinal(Avion dato)
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

void ListaCircularDis::eliminarInicio()
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

void ListaCircularDis::eliminarFinal()
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

void ListaCircularDis::visualizarLista()
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
            std::cout << nodoDato.vuelo << std::endl; // Imprime el número de vuelo
            actual = actual->getSiguiente();
        } while (actual != primero);
    }
}

void ListaCircularDis::generarReporte(){
    if (estaVacia()){
        std::cout << "La lista está vacía\n" << std::endl;
    }
    else
    {
        std::ofstream archivo;
        archivo.open("grafica_LC_Disponible.dot", std::ios::out);
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
        system("dot -Tpng grafica_LC_Disponible.dot -o grafica_LC_Disponible.png");
        system("start grafica_LC_Disponible.png");
    }
}

ListaCircularDis::~ListaCircularDis()
{
    while (!estaVacia()) {
        eliminarInicio();
    }
}

#endif //CIRCULARDOBLEDIS_H
