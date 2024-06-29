#include <iostream>
#include "CargaAviones.h"
#include "CargaComandos.h"
#include "CargaPilotos.h"
using  namespace std;


void opcion1() {
    //CargaAviones::OpcionesAviones();
    CargaAviones::OpcionesAviones();
}

void opcion2() {
    CargaPilotos::OpcionesPilotos();
}

void opcion3() {
    //CargaPasajeros cargaPasajeros;
    //CargaComandos cargaComandos(cargaPasajeros);
    //cargaComandos.LeerComandos();
    std::cout << "Opcion 3" << std::endl;
}

void opcion4() {
    CargaComandos comandos;
    comandos.LeerComandos();
}

void opcion5() {
    std::cout << "Opcion 5" << std::endl;
}

void opcion6() {
    std::cout << "Opcion 6" << std::endl;
}

void opcion7() {
    std::cout << "Opcion 7" << std::endl;
}


int main() {
    int opcion;
    bool salir = false;

    while(!salir){

        cout << "*------Menu principal---------*" << endl;
        cout << "| 1. Carga de aviones         |" << endl;
        cout << "* 2. Carga de pilotos         *" << endl;
        cout << "| 3. Carga de rutas           |" << endl;
        cout << "* 4. Carga de comandos        *" << endl;
        cout << "| 5. Consultar hora de vuelo  |" << endl;
        cout << "* 6. Recomendar ruta          *" << endl;
        cout << "| 7. Visualizar reportes      |" << endl;
        cout << "*-------- 8.Salir ------------*" << endl;
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
                opcion6();
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