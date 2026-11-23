cmake_minimum_required(VERSION 4.3)
project(RielesMuertos)

set(CMAKE_CXX_STANDARD 20)

add_executable(RielesMuertos main.cpp
        include/PersonajeBase.h
        src/PersonajeBase.cpp
        include/Personaje.h
        src/Personaje.cpp
        include/Objeto.h
        src/Objeto.cpp
        include/Arma.h
        src/Arma.cpp
        include/Villano.h
        src/Villano.cpp
        include/Armadura.h
        src/Armadura.cpp
        include/JefeFinal.h
        src/JefeFinal.cpp
        include/Tienda.h
        src/Tienda.cpp
        include/Tren.h
        src/Tren.cpp
        include/GestorPartida.h
        src/GestorPartida.cpp
)
target_include_directories(RielesMuertos PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)