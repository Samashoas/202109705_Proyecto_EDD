#include "ArbolBB.h"

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

void ArbolBB::eliminarPorId(const std::string& numero_de_id) {
    NodoPilotos* nodo = buscarNodoPorId(raiz, numero_de_id);
    if (nodo != nullptr) {
        int horas_de_vuelo = nodo->getPiloto().horas_de_vuelo;
        raiz = eliminarNodo(raiz, horas_de_vuelo);
    }
}

NodoPilotos* ArbolBB::eliminarNodo(NodoPilotos* nodoPtr, int horas_de_vuelo) {
    if (nodoPtr == nullptr) {
        return nodoPtr;
    }

    if (horas_de_vuelo < nodoPtr->getPiloto().horas_de_vuelo) {
        nodoPtr->setSiguiente(eliminarNodo(nodoPtr->getSiguiente(), horas_de_vuelo));
    } else if (horas_de_vuelo > nodoPtr->getPiloto().horas_de_vuelo) {
        nodoPtr->setAnterior(eliminarNodo(nodoPtr->getAnterior(), horas_de_vuelo));
    } else {
        // Nodo con solo un hijo o sin hijos
        if (nodoPtr->getSiguiente() == nullptr) {
            NodoPilotos* temp = nodoPtr->getAnterior();
            delete nodoPtr;
            return temp;
        } else if (nodoPtr->getAnterior() == nullptr) {
            NodoPilotos* temp = nodoPtr->getSiguiente();
            delete nodoPtr;
            return temp;
        }

        // Nodo con dos hijos: Obtener el sucesor inorden (el más pequeño en el subárbol derecho)
        NodoPilotos* temp = encontrarMinimo(nodoPtr->getSiguiente());

        // Copiar el contenido del sucesor inorden a este nodo
        nodoPtr->setPiloto(temp->getPiloto());

        // Eliminar el sucesor inorden
        nodoPtr->setSiguiente(eliminarNodo(nodoPtr->getSiguiente(), temp->getPiloto().horas_de_vuelo));
    }
    return nodoPtr;
}

NodoPilotos* ArbolBB::encontrarMinimo(NodoPilotos* nodoPtr) {
    NodoPilotos* actual = nodoPtr;
    while (actual && actual->getAnterior() != nullptr) {
        actual = actual->getAnterior();
    }
    return actual;
}

NodoPilotos* ArbolBB::encontrarMaximo(NodoPilotos* nodoPtr) {
    NodoPilotos* actual = nodoPtr;
    while (actual && actual->getSiguiente() != nullptr) {
        actual = actual->getSiguiente();
    }
    return actual;
}

NodoPilotos* ArbolBB::buscarNodoPorId(NodoPilotos* nodoPtr, const std::string& numero_de_id) {
    if (nodoPtr == nullptr) {
        return nullptr;
    }

    if (numero_de_id == nodoPtr->getPiloto().numero_de_id) {
        return nodoPtr;
    }

    NodoPilotos* encontrado = buscarNodoPorId(nodoPtr->getSiguiente(), numero_de_id);
    if (encontrado != nullptr) {
        return encontrado;
    }
    return buscarNodoPorId(nodoPtr->getAnterior(), numero_de_id);
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
        archivo << "labelloc=\"t\";" << std::endl; // Posiciona la etiqueta en la parte superior
        archivo << "label=\"Arbol BB Pilotos\";" << std::endl; // Define la etiqueta (título)

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