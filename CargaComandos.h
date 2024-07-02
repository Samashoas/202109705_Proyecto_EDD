#ifndef CARGACOMANDOS_H
#define CARGACOMANDOS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "THash.h"
//#include "arbolBB.h"

class CargaComandos {
public:
    CargaComandos();
    ~CargaComandos();
    void cargarComandos(const std::string& nombreArchivo);
    static void OpcionesComandos();
};

#endif //CARGACOMANDOS_H