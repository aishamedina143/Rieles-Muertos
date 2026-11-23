//
// Created by aisha on 20/11/2026.
//
#pragma once
#ifndef RIELESMUERTOS_OBJETO_H
#define RIELESMUERTOS_OBJETO_H
#include "PersonajeBase.h"


#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Personaje;
class Objeto {
protected:
    string nombre;
    double precio;
    int cantidad;
    double precioVenta;
    bool acumulable;

    public:
    Objeto(string nombre, double precio, int cantidad, double precioVenta, bool acumulable);
    virtual ~Objeto();
    string getNombre();
    double getPrecio();
    int getCantidad();
    double getPrecioVenta();
    bool esAcumulable();
    virtual bool usar(Personaje& personaje);
    virtual bool esArma();
    virtual bool esArmadura();
    void aumentarCantidad(int cantidad);
    void disminuirCantidad(int cantidad);

};
#endif //RIELESMUERTOS_OBJETO_H