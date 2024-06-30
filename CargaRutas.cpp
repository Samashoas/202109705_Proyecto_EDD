//
// Created by jpsam on 29/06/2024.
//

#include "CargaRutas.h"
#include <fstream>
#include <iostream>
#include <sstream>


CargaRutas::CargaRutas() {
}

CargaRutas::~CargaRutas() {
}

GrafoDirigido grafo;

void CargaRutas::cargarDesdeArchivo(std::string nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if(!archivo.is_open()){
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string origen, destino, distancia_str;
        if (std::getline(iss, origen, '/') && std::getline(iss, destino, '/') && std::getline(iss, distancia_str)) {
            Ruta ruta;
            ruta.origen = origen;
            ruta.destino = destino;
            try {
                ruta.distancia = std::stoi(distancia_str);
                rutas.push_back(ruta);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error al convertir la distancia a número: " << distancia_str << std::endl;
            }
        }
    }
    archivo.close();
}

void CargaRutas::OpcionesRutas() {
    std::string nombre_archivo;
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> nombre_archivo;

    CargaRutas instancia;

    instancia.cargarDesdeArchivo(nombre_archivo);

    for (size_t i = 0; i < instancia.rutas.get_size(); i++) {
        Ruta& ruta = instancia.rutas[i];
        std::cout << " " << std::endl;
        std::cout << "Origen: " << ruta.origen << std::endl;
        std::cout << "Destino: " << ruta.destino << std::endl;
        std::cout << "Distancia: " << ruta.distancia << std::endl;
        grafo.agregarArista(ruta.origen, ruta.destino, ruta.distancia);
    }

    grafo.mostrarGrafo();
}

void CargaRutas::addRuta(const Ruta& ruta) {
    rutas.push_back(ruta);
}

void CargaRutas::GrafoDRutas() {
    grafo.generarArchivoDOT();
}

void CargaRutas::Shortcut() {
    std::string origen, destino;
    std::cout << "Ingrese la ciudad origen: ";
    std::cin >> origen;
    std::cout << "Ingrese la ciudad destino: ";
    std::cin >> destino;
    grafo.FindShortcut(origen, destino);
}



