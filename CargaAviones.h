//
// Created by jpsam on 12/06/2024.
//

#ifndef CARGAAVIONES_H
#define CARGAAVIONES_H

#include <string>
#include <nlohmann/json.hpp>
#include "MiVector.h"

struct Avion {
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string ciudad_destino;
    std::string estado;
};

class CargaAviones {
public:
    CargaAviones();
    ~CargaAviones();
    void cargarDesdeArchivo(std::string nombre_archivo);
    static void OpcionesAviones();
    static void reportePrueba();
    void addAvion(const Avion& avion);

private:
    MiVector<Avion> aviones;
};

#endif //CARGAAVIONES_H