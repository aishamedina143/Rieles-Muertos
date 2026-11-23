//
// Created by aisha on 20/11/2026.
//
#include "JefeFinal.h"
#include <iostream>
using namespace std;

JefeFinal::JefeFinal(string nombre, int vida, string tipo, int dano,
                     double recompensa, string habilidadEspecial, int danoEspecial)
    : Villano(nombre, vida, tipo, dano, recompensa) {

    this->habilidadEspecial = habilidadEspecial;
    this->danoEspecial = danoEspecial;
}
int JefeFinal::usarHabilidadEspecial() {
    cout << "El jefe utiliza " << habilidadEspecial << "!" << endl;
    cout << "Inflige " << danoEspecial << " puntos de dano." << endl;
    return danoEspecial;
}
int JefeFinal::atacar() {
    return dano;
}