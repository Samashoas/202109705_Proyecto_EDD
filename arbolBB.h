//
// Created by jpsam on 28/06/2024.
//

#ifndef ARBOLBB_H
#define ARBOLBB_H
#include "CargaPilotos.h"
#include "NodoPiloto.h"
//
// Created by jpsam on 28/06/2024.
//
class ArbolBB
{
private:
    NodoPilotos* raiz;
    ofstream archivo;
    Piloto nodoDato;
public:
    int recorrido = 0;
    ArbolBB();
    bool estaVacio();
    void insertar(Piloto dato);
    NodoPilotos* insertarNodo(Piloto dato, NodoPilotos* nodoPtr);
    void buscar(Piloto dato);
    Piloto buscarNodo(Piloto dato, NodoPilotos* nodoPtr);

    void Recorrido();
    void Recorrido(NodoPilotos* nodoPtr);

    void generarReporte();
    void imprimirNodo(NodoPilotos* nodoPtr);
    ~ArbolBB();
};

ArbolBB::ArbolBB()
{
    raiz = nullptr;
}

bool ArbolBB::estaVacio()
{
    return (raiz == nullptr);
}

void ArbolBB::insertar(Piloto dato)
{
    raiz = insertarNodo(dato, raiz);
}

NodoPilotos* ArbolBB::insertarNodo(Piloto dato, NodoPilotos* nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        NodoPilotos* nuevo = new NodoPilotos(dato);
        nodoPtr = nuevo;
    }
    else if (dato.horas_de_vuelo < nodoPtr->getPiloto().horas_de_vuelo)
    {
        nodoPtr->setSiguiente(insertarNodo(dato, nodoPtr->getSiguiente()));
    }
    else if (dato.horas_de_vuelo > nodoPtr->getPiloto().horas_de_vuelo)
    {
        nodoPtr->setAnterior(insertarNodo(dato, nodoPtr->getAnterior()));
    }
    else{
        cout << "Nodo duplicado\n";
    }
    return nodoPtr;
}

void ArbolBB::buscar(Piloto dato)
{
    cout << "Recorrido del nodo encontrado: " << buscarNodo(dato, raiz).horas_de_vuelo << ", " << recorrido;
}

Piloto ArbolBB::buscarNodo(Piloto dato, NodoPilotos* nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        cout << "Nodo no encontrado\n";
        return Piloto(); // Devuelve un piloto vacío si el nodo no se encuentra
    }
    else if(dato.horas_de_vuelo == nodoPtr->getPiloto().horas_de_vuelo){
        recorrido++;
        return nodoPtr->getPiloto();
    }
    else if(dato.horas_de_vuelo < nodoPtr->getPiloto().horas_de_vuelo)
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getSiguiente());
    }
    else if(dato.horas_de_vuelo > nodoPtr->getPiloto().horas_de_vuelo)
    {
        recorrido ++;
        return buscarNodo(dato, nodoPtr->getAnterior());
    }

}

void ArbolBB::Recorrido()
{
    Recorrido(raiz);
}

void ArbolBB::Recorrido(NodoPilotos* nodoPtr)
{
    if (nodoPtr != nullptr)
    {
        //PREORDEN
        cout << nodoPtr->getPiloto().horas_de_vuelo << endl;
        Recorrido(nodoPtr->getSiguiente());
        Recorrido(nodoPtr->getAnterior());

        //INORDEN
        /*Recorrido(nodoPtr->getSiguiente());
        cout << nodoPtr->getPiloto().numero_de_id << endl;
        Recorrido(nodoPtr->getAnterior());*/

        //POSTORDEN
    }

}

void ArbolBB::generarReporte()
{
    if (ArbolBB::estaVacio()){}
    else
    {
        archivo.open("grafica_arbol.dot", ios::out);
        archivo << "digraph G { " << endl;

        imprimirNodo(raiz);

        archivo << " }";
        archivo.close();
        system("dot -Tpng grafica_arbol.dot -o grafica_arbol.png");
        system("start grafica_arbol.png");
    }

}

void ArbolBB::imprimirNodo(NodoPilotos* nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }
    if (nodoPtr->getSiguiente() != nullptr)
    {
        nodoDato = nodoPtr->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << "->";
        nodoDato = nodoPtr->getSiguiente()->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << ";";
    }
    imprimirNodo(nodoPtr->getSiguiente());

    if (nodoPtr->getAnterior()!= nullptr)
    {
        nodoDato = nodoPtr->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << "->";
        nodoDato = nodoPtr->getAnterior()->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << ";";
    }
    imprimirNodo(nodoPtr->getAnterior());

}

ArbolBB::~ArbolBB()
{
}


#endif //ARBOLBB_H
