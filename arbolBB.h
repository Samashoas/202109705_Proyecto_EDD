#ifndef ARBOLBB_H
#define ARBOLBB_H
#include "CargaPilotos.h"
#include "NodoPiloto.h"
#include <fstream>

class ArbolBB {
private:
    NodoPilotos* raiz;
    std::ofstream archivo;
    Piloto nodoDato;

    NodoPilotos* eliminarNodo(NodoPilotos* nodoPtr, const std::string& numero_de_id);
    NodoPilotos* encontrarMinimo(NodoPilotos* nodoPtr);

public:
    int recorrido = 0;
    ArbolBB();
    bool estaVacio();
    void insertar(Piloto dato);
    NodoPilotos* insertarNodo(Piloto dato, NodoPilotos* nodoPtr);
    void buscar(Piloto dato);
    Piloto buscarNodo(Piloto dato, NodoPilotos* nodoPtr);
    void eliminar(const std::string& numero_de_id);

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

ArbolBB::ArbolBB() {
    raiz = nullptr;
}

bool ArbolBB::estaVacio() {
    return (raiz == nullptr);
}

void ArbolBB::insertar(Piloto dato) {
    raiz = insertarNodo(dato, raiz);
}

NodoPilotos* ArbolBB::insertarNodo(Piloto dato, NodoPilotos* nodoPtr) {
    if (nodoPtr == nullptr) {
        NodoPilotos* nuevo = new NodoPilotos(dato);
        nodoPtr = nuevo;
    } else if (dato.horas_de_vuelo < nodoPtr->getPiloto().horas_de_vuelo) {
        nodoPtr->setSiguiente(insertarNodo(dato, nodoPtr->getSiguiente()));
    } else if (dato.horas_de_vuelo > nodoPtr->getPiloto().horas_de_vuelo) {
        nodoPtr->setAnterior(insertarNodo(dato, nodoPtr->getAnterior()));
    } else {
        std::cout << "Nodo duplicado\n";
    }
    return nodoPtr;
}

void ArbolBB::buscar(Piloto dato) {
    std::cout << "Recorrido del nodo encontrado: " << buscarNodo(dato, raiz).horas_de_vuelo << ", " << recorrido;
}

Piloto ArbolBB::buscarNodo(Piloto dato, NodoPilotos* nodoPtr) {
    if (nodoPtr == nullptr) {
        std::cout << "Nodo no encontrado\n";
        return Piloto(); // Devuelve un piloto vacío si el nodo no se encuentra
    } else if (dato.horas_de_vuelo == nodoPtr->getPiloto().horas_de_vuelo) {
        recorrido++;
        return nodoPtr->getPiloto();
    } else if (dato.horas_de_vuelo < nodoPtr->getPiloto().horas_de_vuelo) {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getSiguiente());
    } else if (dato.horas_de_vuelo > nodoPtr->getPiloto().horas_de_vuelo) {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getAnterior());
    }
}

void ArbolBB::eliminar(const std::string& numero_de_id) {
    raiz = eliminarNodo(raiz, numero_de_id);
}

NodoPilotos* ArbolBB::eliminarNodo(NodoPilotos* nodoPtr, const std::string& numero_de_id) {
    if (nodoPtr == nullptr) {
        return nodoPtr;
    }

    if (numero_de_id < nodoPtr->getPiloto().numero_de_id) {
        nodoPtr->setSiguiente(eliminarNodo(nodoPtr->getSiguiente(), numero_de_id));
    } else if (numero_de_id > nodoPtr->getPiloto().numero_de_id) {
        nodoPtr->setAnterior(eliminarNodo(nodoPtr->getAnterior(), numero_de_id));
    } else {
        if (nodoPtr->getSiguiente() == nullptr) {
            NodoPilotos* temp = nodoPtr->getAnterior();
            delete nodoPtr;
            return temp;
        } else if (nodoPtr->getAnterior() == nullptr) {
            NodoPilotos* temp = nodoPtr->getSiguiente();
            delete nodoPtr;
            return temp;
        }

        NodoPilotos* temp = encontrarMinimo(nodoPtr->getSiguiente());
        nodoPtr->getPiloto() = temp->getPiloto();
        nodoPtr->setSiguiente(eliminarNodo(nodoPtr->getSiguiente(), temp->getPiloto().numero_de_id));
    }
    return nodoPtr;
}

NodoPilotos* ArbolBB::encontrarMinimo(NodoPilotos* nodoPtr) {
    NodoPilotos* actual = nodoPtr;
    while (actual && actual->getAnterior() != nullptr)
        actual = actual->getAnterior();
    return actual;
}

void ArbolBB::imprimirPreorden() {
    std::cout << "Recorrido Preorden: " << std::endl;
    RecorridoPreorden(raiz);
    std::cout << std::endl;
}

void ArbolBB::imprimirInorden() {
    std::cout << "Recorrido Inorden: " << std::endl;
    RecorridoInorden(raiz);
    std::cout << std::endl;
}

void ArbolBB::imprimirPostorden() {
    std::cout << "Recorrido Postorden: " << std::endl;
    RecorridoPostorden(raiz);
    std::cout << std::endl;
}

void ArbolBB::RecorridoPreorden(NodoPilotos* nodoPtr) {
    if (nodoPtr != nullptr) {
        std::cout << nodoPtr->getPiloto().horas_de_vuelo << std::endl;
        RecorridoPreorden(nodoPtr->getSiguiente());
        RecorridoPreorden(nodoPtr->getAnterior());
    }
}

void ArbolBB::RecorridoInorden(NodoPilotos* nodoPtr) {
    if (nodoPtr != nullptr) {
        RecorridoInorden(nodoPtr->getSiguiente());
        std::cout << nodoPtr->getPiloto().horas_de_vuelo << std::endl;
        RecorridoInorden(nodoPtr->getAnterior());
    }
}

void ArbolBB::RecorridoPostorden(NodoPilotos* nodoPtr) {
    if (nodoPtr != nullptr) {
        RecorridoPostorden(nodoPtr->getSiguiente());
        RecorridoPostorden(nodoPtr->getAnterior());
        std::cout << nodoPtr->getPiloto().horas_de_vuelo << std::endl;
    }
}

void ArbolBB::generarReporte() {
    if (ArbolBB::estaVacio()) {} else {
        archivo.open("grafica_arbol.dot", std::ios::out);
        archivo << "digraph G { " << std::endl;

        imprimirNodo(raiz);

        archivo << " }";
        archivo.close();
        system("dot -Tpng grafica_arbol.dot -o grafica_arbol.png");
        system("start grafica_arbol.png");
    }
}

void ArbolBB::imprimirNodo(NodoPilotos* nodoPtr) {
    if (nodoPtr == nullptr) {
        return;
    }
    if (nodoPtr->getSiguiente() != nullptr) {
        nodoDato = nodoPtr->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << "->";
        nodoDato = nodoPtr->getSiguiente()->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << ";";
    }
    imprimirNodo(nodoPtr->getSiguiente());

    if (nodoPtr->getAnterior() != nullptr) {
        nodoDato = nodoPtr->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << "->";
        nodoDato = nodoPtr->getAnterior()->getPiloto();
        archivo << nodoDato.horas_de_vuelo;
        archivo << ";";
    }
    imprimirNodo(nodoPtr->getAnterior());
}

ArbolBB::~ArbolBB() {}

#endif // ARBOLBB_H
