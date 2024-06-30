//
// Created by jpsam on 28/06/2024.
//

#ifndef CARGAPILOTOS_H
#define CARGAPILOTOS_H
#include <string>
#include <nlohmann/json.hpp>
#include "MiVector.h"

struct Piloto {
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_id;
    std::string vuelo;
    int horas_de_vuelo;
    std::string tipo_de_licencia;
};

std::ostream& operator<<(std::ostream& os, const Piloto& piloto);

class CargaPilotos {
public:
    CargaPilotos();
    ~CargaPilotos();
    void cargarDesdeArchivo(std::string nombre_archivo);
    void addPiloto(const Piloto& piloto);
    static void OpcionesPilotos();  // Quita el 'static' aquí
    static void ArbolPilotos();
    static void RInorden();
    static void RPreorden();
    static void RPostorden();
    static void RTablaHash();
private:
    MiVector<Piloto> pilotos;
};

#endif //CARGAPILOTOS_H
