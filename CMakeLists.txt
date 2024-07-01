cmake_minimum_required(VERSION 3.28)
project(202109705_Proyecto_EDD)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.5
)
FetchContent_MakeAvailable(json)

add_executable(202109705_Proyecto_EDD main.cpp
        CargaAviones.cpp
        CargaAviones.h
        MiVector.h
        MyArrasy.h
        nodoAv.h
        CircularDobleMan.h
        CargaComandos.cpp
        CargaComandos.h
        nodoAv.h
        Btree.h
        CargaPilotos.cpp
        CargaPilotos.h
        arbolBB.h
        NodoPiloto.h
        THash.h
        CargaRutas.cpp
        CargaRutas.h
        GrafoDirigido.cpp
        GrafoDirigido.h
        NodoMatriz.h
        MatrizDisp.h
        NodoListaSimple.h
        ListaSimple.h
)
target_link_libraries(202109705_Proyecto_EDD PRIVATE nlohmann_json::nlohmann_json)