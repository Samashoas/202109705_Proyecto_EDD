#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H
#include <string>
using namespace std;

class NodoMatrix
{
private:
    string dato;
    int fila;
    int columna;
    NodoMatrix* siguiente;
    NodoMatrix* anterior;
    NodoMatrix* arriba;
    NodoMatrix* abajo;
public:
    NodoMatrix(string d, int f, int c);
    string getDato();
    int getFila();
    int getColumna();
    NodoMatrix* getSiguiente();
    NodoMatrix* getAnterior();
    NodoMatrix* getArriba();
    NodoMatrix* getAbajo();
    void setDato(string d);
    void setFila(int f);
    void setColumna(int c);
    void setSiguiente(NodoMatrix* s);
    void setAnterior(NodoMatrix* a);
    void setArriba(NodoMatrix* a);
    void setAbajo(NodoMatrix* b);
    ~NodoMatrix();
};

NodoMatrix::NodoMatrix(string d, int f, int c)
{
    dato = d;
    fila = f;
    columna = c;
    siguiente = nullptr;
    anterior = nullptr;
    arriba = nullptr;
    abajo = nullptr;
}

string NodoMatrix::getDato()
{
    return dato;
}

int NodoMatrix::getFila()
{
    return fila;
}

int NodoMatrix::getColumna()
{
    return columna;
}

NodoMatrix* NodoMatrix::getSiguiente()
{
    return siguiente;
}

NodoMatrix* NodoMatrix::getAnterior()
{
    return anterior;
}

NodoMatrix* NodoMatrix::getArriba()
{
    return arriba;
}

NodoMatrix* NodoMatrix::getAbajo()
{
    return abajo;
}

void NodoMatrix::setDato(string d)
{
    dato = d;
}

void NodoMatrix::setFila(int f)
{
    fila = f;
}

void NodoMatrix::setColumna(int c)
{
    columna = c;
}

void NodoMatrix::setSiguiente(NodoMatrix* s)
{
    siguiente = s;
}

void NodoMatrix::setAnterior(NodoMatrix* a)
{
    anterior = a;
}

void NodoMatrix::setArriba(NodoMatrix* a)
{
    arriba = a;
}

void NodoMatrix::setAbajo(NodoMatrix* b)
{
    abajo = b;
}

NodoMatrix::~NodoMatrix()
{
}
#endif //NODOMATRIZ_H
