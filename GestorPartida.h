//
// Created by aisha on 21/11/2026.
//
#pragma once

#ifndef RIELESMUERTOS_GESTORPARTIDA_H
#define RIELESMUERTOS_GESTORPARTIDA_H
#include <iostream>
#include <fstream>
#include <string>
#include "Personaje.h"
#include "Tren.h"

using namespace std;

class GestorPartida {
private:
    string nombreArchivo;

public:
    GestorPartida();

    void guardarPartida(Personaje& personaje, Tren& tren);
    bool cargarPartida(Personaje& personaje, Tren& tren);
};
#endif //RIELESMUERTOS_GESTORPARTIDA_H
