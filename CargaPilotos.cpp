//
// Created by jpsam on 28/06/2024.
//

#include "CargaPilotos.h"
#include <fstream>
#include <iostream>
#include "arbolBB.h"
#include "THash.h"

using nlohmann::json;

CargaPilotos::CargaPilotos() {
    // Constructor implementation
}

CargaPilotos::~CargaPilotos() {
    // Destructor implementation
}
TablaHash THash(18);
ArbolBB arbol_bb;
void CargaPilotos::cargarDesdeArchivo(std::string nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if(!archivo.is_open()){
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }

    json j;
    archivo >> j;

    for (const auto& item : j) {
        Piloto piloto;
        piloto.nombre = item["nombre"];
        piloto.nacionalidad = item["nacionalidad"];
        piloto.numero_de_id = item["numero_de_id"];
        piloto.vuelo = item["vuelo"];
        piloto.horas_de_vuelo = item["horas_de_vuelo"];
        piloto.tipo_de_licencia = item["tipo_de_licencia"];

        THash.insertar(piloto);
        arbol_bb.insertar(piloto);

        pilotos.push_back(piloto);
    }
    arbol_bb.generarReporte();
    THash.generarReporte();
}

void CargaPilotos::OpcionesPilotos() {
    std::string nombre_archivo;
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> nombre_archivo;

    CargaPilotos instancia;
    instancia.cargarDesdeArchivo(nombre_archivo);

    for (size_t i = 0; i < instancia.pilotos.get_size(); i++) {
        Piloto& piloto = instancia.pilotos[i];
        std::cout << " " << std::endl;
        std::cout << "------Pilotos registrados------" << std::endl;
        std::cout << "nombre: " << piloto.nombre << std::endl;
        std::cout << "nacionalidad: " << piloto.nacionalidad << std::endl;
        std::cout << "Num. de id: " << piloto.numero_de_id << std::endl;
        std::cout << "vuelo: " << piloto.vuelo << std::endl;
        std::cout << "Horas de vuelo: " << piloto.horas_de_vuelo << std::endl;
        std::cout << "Tipo de licencia: " << piloto.tipo_de_licencia << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
    THash.imprimir();
}

void CargaPilotos::ArbolPilotos() {
    arbol_bb.generarReporte();
}

void CargaPilotos::RPreorden() {
    arbol_bb.imprimirPreorden();
}

void CargaPilotos::RInorden() {
    arbol_bb.imprimirInorden();
}

void CargaPilotos::RPostorden() {
    arbol_bb.imprimirPostorden();
}

void CargaPilotos::RTablaHash() {
    THash.generarReporte();
}
