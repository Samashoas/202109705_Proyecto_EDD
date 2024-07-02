#ifndef NODOPILOTO_H
#define NODOPILOTO_H

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
    void setPiloto(const Piloto& piloto);
    Piloto getPiloto();
};

#endif // NODOPILOTO_H