//
// Created by aisha on 20/11/2026.
//
#pragma once

#ifndef RIELESMUERTOS_ARMADURA_H
#define RIELESMUERTOS_ARMADURA_H
#include "Objeto.h"

class Armadura : public Objeto {
private:
    int defensa;
    int durabilidad;
public:
    Armadura(string nombre, double precio, int cantidad,
         double precioVenta, bool acumulable,
         int defensa, int durabilidad);

    ~Armadura();

    int reducirDano(int cantidad);
    bool usar() ;
    int getDefensa();
    int getDurabilidad();
    bool esArmadura() override;
};
#endif //RIELESMUERTOS_ARMADURA_H
