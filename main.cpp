#include <iostream>
#include "CargaAviones.h"
#include "CargaComandos.h"
#include "CargaPilotos.h"
#include "CargaRutas.h"
using  namespace std;

void opcionABBPilotos() {
    int subOpcion2;
    bool regresar = false;

    while(!regresar){
        std::cout << "*------Recorrido ABB-----*" << std::endl;
        std::cout << "| 1. Preorden            |" << std::endl;
        std::cout << "* 2. Inorden             *" << std::endl;
        std::cout << "| 3. Postorden           |" << std::endl;
        std::cout << "*----- 4. Regresar ------*" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> subOpcion2;

        switch (subOpcion2){
            case 1:
                CargaPilotos::RPreorden();
            break;
            case 2:
                CargaPilotos::RInorden();
            break;
            case 3:
                CargaPilotos::RPostorden();
            break;
            case 4:
                std::cout << "Regresando al menu principal..." << std::endl;
            regresar = true;
            break;
            default:
                std::cout << "Opcion no valida" << std::endl;
            break;
        }
        if(!regresar){
            std::cout << "Presione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

void opcion1() {
    CargaAviones::OpcionesAviones();
}

void opcion2() {
    CargaPilotos::OpcionesPilotos();
}

void opcion3() {
    CargaRutas::OpcionesRutas();
}

void opcion4() {
    CargaComandos comandos;
    comandos.LeerComandos();
}

void opcion5() {
    std::cout << "Opcion 5" << std::endl;
}

void opcion6() {
    std::cout << "Opcion 5" << std::endl;
}

void opcion7() {
    int subOpcion;
    bool regresar = false;

    while(!regresar){
        std::cout << "*------Submenu de reportes-----*" << std::endl;
        std::cout << "| 1. Arbol B de aviones        |" << std::endl;
        std::cout << "* 2. Lista de aviones          *" << std::endl;
        std::cout << "| 3. Arbol binario de pilotos  |" << std::endl;
        std::cout << "| 4. Tabla hash de pilotos     |" << std::endl;
        std::cout << "| 5. Grafo dirigido de rutas   |" << std::endl;
        std::cout << "| 6. Matriz dispersa           |" << std::endl;
        std::cout << "*-------- 7. Regresar --------*" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> subOpcion;

        switch (subOpcion){
            case 1:
                CargaAviones::ArbolAviones();
            break;
            case 2:
                CargaAviones::ListaAviones();
            break;
            case 3:
                CargaPilotos::ArbolPilotos();
                opcionABBPilotos();
            break;
            case 4:
                CargaPilotos::RTablaHash();
            break;
            case 7:
                std::cout << "Regresando al menu principal..." << std::endl;
            regresar = true;
            break;
            default:
                std::cout << "Opcion no valida" << std::endl;
            break;
        }
        if(!regresar){
            std::cout << "Presione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}


int main() {
    int opcion;
    bool salir = false;

    while(!salir){

        cout << "*------------Menu principal-----------*" << endl;
        cout << "| 1. Carga de aviones                 |" << endl;
        cout << "* 2. Carga de pilotos                 *" << endl;
        cout << "| 3. Carga de rutas                   |" << endl;
        cout << "* 4. Carga de comandos                *" << endl;
        cout << "| 5. Consultar hora de vuelo(PILOTO)  |" << endl;
        cout << "* 6. Recomendar ruta                  *" << endl;
        cout << "| 7. Visualizar reportes              |" << endl;
        cout << "*------------- 8.Salir ---------------*" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion){
            case 1:
                opcion1();
            break;
            case 2:
                opcion2();
            break;
            case 3:
                opcion3();
            break;
            case 4:
                opcion4();
            break;
            case 5:
                opcion5();
            break;
            case 6:
                opcion6();
            break;
            case 7:
                opcion7();
            break;
            case 8:
                cout << "Adios!" << endl;
                salir = true;
            break;
            default:
                cout << "Opcion no valida" << endl;
            break;
        }

        if(!salir){
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }
    return 0;
}