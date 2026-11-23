//
// Created by aisha on 20/11/2026.
//
#pragma once
#ifndef RIELESMUERTOS_VILLANO_H
#define RIELESMUERTOS_VILLANO_H
#include "PersonajeBase.h"
class Villano : public PersonajeBase {
    protected:
    string tipo;
    int dano;
    double recompensa;
public:
    Villano(string nombre, int vida, string tipo, int dano, double recompensa);
    ~Villano();
    int atacar() override;
    void perseguir();
    void aparecer();
    double getRecompensa();

};
#endif //RIELESMUERTOS_VILLANO_H
