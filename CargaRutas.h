//
// Created by jpsam on 29/06/2024.
//

#ifndef CARGARUTAS_H
#define CARGARUTAS_H
#include <string>
#include "MiVector.h"

struct Ruta {
    std::string origen;
    std::string destino;
    int distancia;
};

std::ostream& operator<<(std::ostream& os, const Ruta& ruta);

class CargaRutas {
public:
    CargaRutas();
    ~CargaRutas();
    void cargarDesdeArchivo(std::string nombre_archivo);
    void addRuta(const Ruta& ruta);
    static void OpcionesRutas();
private:
    MiVector<Ruta> rutas;
};

#endif //CARGARUTAS_H
