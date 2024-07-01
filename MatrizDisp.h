//
// Created by jpsam on 30/06/2024.
//

#ifndef MATRIZDISP_H
#define MATRIZDISP_H
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
#include "NodoMatriz.h"

class Matriz
{
private:
    /* data */
public:
    NodoMatrix* root;
    Matriz(/* args */);
    NodoMatrix* buscarFila(int fila, NodoMatrix* inicio);
    NodoMatrix* buscarColumna(int columna, NodoMatrix* inicio);
    NodoMatrix* crearFila(int fila);
    NodoMatrix* crearColumna(int columna);
    void insertar(string dato, int fila, int columna);
    void generarArchivoDOT(const string& nombreArchivo) const;
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new NodoMatrix("Root", -1, -1); //-1 y -1 para encabezado root
}

NodoMatrix* Matriz::buscarFila(int fila, NodoMatrix* inicio)
{
    NodoMatrix* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; //Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera fila
}

NodoMatrix* Matriz::buscarColumna(int columna, NodoMatrix* inicio)
{
    NodoMatrix* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; //Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera columna
}

NodoMatrix* Matriz::crearFila(int fila)
{
    NodoMatrix* f = new NodoMatrix("Fila", fila, -1);
    NodoMatrix* aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

NodoMatrix* Matriz::crearColumna(int columna)
{
    NodoMatrix* c = new NodoMatrix("Columna", -1, columna);
    NodoMatrix* aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(string dato, int fila, int columna)
{
    NodoMatrix* nodoDato = new NodoMatrix(dato, fila, columna);
    NodoMatrix* nodoFila; //Para saber en que fila insertar
    NodoMatrix* nodoColumna; //Para saber en que columna insertar

    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    //REVISAMOS SI EXISTEN LOS ENCABEZADOS
    if (nodoFila == nullptr && nodoColumna == nullptr) //Caso 1
    {
        nodoFila = crearFila(fila);
        nodoColumna = crearColumna(columna);
    }
    else if (nodoFila != nullptr && nodoColumna == nullptr) //Caso 2
    {
        nodoColumna = crearColumna(columna);
    }
    else if (nodoFila == nullptr && nodoColumna != nullptr)
    {
        nodoFila = crearFila(fila);
    }

    //Insertando nodoDato en la cabecera fila
    NodoMatrix* auxFila = nodoFila;
    while (auxFila != nullptr)
    {
        if (auxFila->getSiguiente() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxFila->setSiguiente(nodoDato);
            nodoDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
    }

    //Insertando nodoDato en la cabecera columna
    NodoMatrix* auxColumna = nodoColumna;
    while (auxColumna != nullptr)
    {
        if (auxColumna->getAbajo() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxColumna->setAbajo(nodoDato);
            nodoDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();
    }
}

void Matriz::generarArchivoDOT(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << "digraph G {" << endl;
    archivo << "node [shape=record];" << endl;

    // Generar nodos para todas las filas y columnas
    NodoMatrix* aux = root;
    while (aux != nullptr) {
        NodoMatrix* auxFila = aux;
        while (auxFila != nullptr) {
            archivo << "nodo" << auxFila << "[label=\"{" << auxFila->getColumna() << "," << auxFila->getFila() << "|" << auxFila->getDato() << "}\"];" << endl;
            auxFila = auxFila->getSiguiente();
        }
        aux = aux->getAbajo();
    }

    // Generar conexiones entre nodos
    aux = root;
    while (aux != nullptr) {
        NodoMatrix* auxFila = aux;
        while (auxFila != nullptr) {
            if (auxFila->getSiguiente() != nullptr) {
                archivo << "nodo" << auxFila << " -> nodo" << auxFila->getSiguiente() << ";" << endl;
            }
            if (auxFila->getAbajo() != nullptr) {
                archivo << "nodo" << auxFila << " -> nodo" << auxFila->getAbajo() << ";" << endl;
            }
            auxFila = auxFila->getSiguiente();
        }
        aux = aux->getAbajo();
    }

    // Generar filas y columnas
    aux = root;
    while (aux != nullptr) {
        NodoMatrix* auxFila = aux;
        archivo << "subgraph cluster_" << auxFila->getFila() << " { style=invis; ";
        while (auxFila != nullptr) {
            archivo << "nodo" << auxFila << "; ";
            auxFila = auxFila->getSiguiente();
        }
        archivo << "}" << endl;
        aux = aux->getAbajo();
    }

    archivo << "}" << endl;
    archivo.close();

    // Llamar a Graphviz para generar la imagen
    string comando = "dot -Tpng " + nombreArchivo + " -o matriz.png";
    system(comando.c_str());

    system("matriz.png");
}

Matriz::~Matriz()
{
}
#endif //MATRIZDISP_H
