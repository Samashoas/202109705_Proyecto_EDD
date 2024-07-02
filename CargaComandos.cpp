#include "CargaComandos.h"
#include "ArbolBB.h" // Incluye aquí ArbolBB.h

extern TablaHash THash;
extern ArbolBB arbol_bb;

CargaComandos::CargaComandos() {
    // Constructor
}

CargaComandos::~CargaComandos() {
    // Destructor
}

void CargaComandos::cargarComandos(const std::string& nombreArchivo) {
    std::ifstream file(nombreArchivo);
    std::string linea;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo\n";
        return;
    }

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string comando;
        getline(ss, comando, '(');

        // Imprimir el comando que se está procesando
        std::cout << "Procesando comando: " << linea << std::endl;

        if (comando == "DarDeBaja") {
            std::string numero_de_id;
            getline(ss, numero_de_id, ')');
            THash.eliminar(numero_de_id);
            arbol_bb.eliminarPorId(numero_de_id);
        }
        // Agrega aquí otros comandos según sea necesario
    }

    file.close();
}